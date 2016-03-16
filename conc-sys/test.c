
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

#define NTHREADS 8

struct complex {
  float real;
  float imag;
};

struct reference {
	// struct complex ** A;
	// struct complex ** B;
	int dimemsion;
	int i;
	int j;
	int final_position;
};

struct finalResult {
	struct complex ** A;
	struct complex ** B;
	struct complex ** C;
	int a_dim1;
	int a_dim2;
	int b_dim2;
};

struct complex ** new_empty_matrix(int dim1, int dim2)
{
  struct complex ** result = malloc(sizeof(struct complex*) * dim1);
  struct complex * new_matrix = malloc(sizeof(struct complex) * dim1 * dim2);
  int i;

  for ( i = 0; i < dim1; i++ ) {
    result[i] = &(new_matrix[i*dim2]);
  }

  return result;
}

struct complex ** gen_random_matrix(int dim1, int dim2)
{
  const int random_range = 512; // constant power of 2
  struct complex ** result;
  int i, j;
  struct timeval seedtime;
  int seed;

  result = new_empty_matrix(dim1, dim2);

  /* use the microsecond part of the current time as a pseudorandom seed */
  gettimeofday(&seedtime, NULL);
  seed = seedtime.tv_usec;
  srandom(seed);

  /* fill the matrix with random numbers */
  for ( i = 0; i < dim1; i++ ) {
    for ( j = 0; j < dim2; j++ ) {
      /* evenly generate values in the range [0, random_range-1)*/
      result[i][j].real = (float)(random() % random_range);
      result[i][j].imag = (float)(random() % random_range);

      /* at no loss of precision, negate the values sometimes */
      /* so the range is now (-(random_range-1), random_range-1)*/
      if (random() & 1) result[i][j].real = -result[i][j].real;
      if (random() & 1) result[i][j].imag = -result[i][j].imag;
    }
  }

  return result;
}

void write_out(struct complex ** a, int dim1, int dim2)
{
  int i, j;

  for ( i = 0; i < dim1; i++ ) {
    for ( j = 0; j < dim2 - 1; j++ ) {
      printf("%.3f + %.3fi ", a[i][j].real, a[i][j].imag);
    }
    printf("%.3f + %.3fi\n", a[i][dim2-1].real, a[i][dim2-1].imag);
  }
}

void free_matrix(struct complex ** matrix) {
  free (matrix[0]); /* free the contents */
  free (matrix); /* free the header */
}

long long time_diff(struct timeval * start, struct timeval * end) {
  return (end->tv_sec - start->tv_sec) * 1000000L + (end->tv_usec - start->tv_usec);
}

void matmulMain(struct complex ** A, struct complex ** B, struct complex ** C, int a_dim1, int a_dim2, int b_dim2)
{
  int i, j, k;

  for ( i = 0; i < a_dim1; i++ ) {
    for( j = 0; j < b_dim2; j++ ) {
      struct complex sum;
      sum.real = 0.0;
      sum.imag = 0.0;
      for ( k = 0; k < a_dim2; k++ ) {
        // the following code does: sum += A[i][k] * B[k][j];
        struct complex product;
        product.real = A[i][k].real * B[k][j].real - A[i][k].imag * B[k][j].imag;
        product.imag = A[i][k].real * B[k][j].imag + A[i][k].imag * B[k][j].real;
        sum.real += product.real;
        sum.imag += product.imag;
      }
      C[i][j] = sum;
    }
  }
}

void * matmul(void * param1) {

	struct finalResult * theMatrix = (struct finalResult *)param1;

	int i, j, k;

  for ( i = 0; i < theMatrix -> a_dim1; i++ ) {
    for( j = 0; j < theMatrix -> b_dim2; j++ ) {
      struct complex sum;
      sum.real = 0.0;
      sum.imag = 0.0;
      for ( k = 0; k < theMatrix -> a_dim2; k++ ) {
        // the following code does: sum += A[i][k] * B[k][j];
        struct complex product;
        // pthread_mutex_lock( &mutex1 );
        product.real = theMatrix -> A[i][k].real * theMatrix -> B[k][j].real - theMatrix -> A[i][k].imag * theMatrix -> B[k][j].imag;
        product.imag = theMatrix -> A[i][k].real * theMatrix -> B[k][j].imag + theMatrix -> A[i][k].imag * theMatrix -> B[k][j].real;
        // pthread_mutex_lock( &mutex1 );
        sum.real += product.real;
        sum.imag += product.imag;
        // pthread_mutex_unlock( &mutex1 );
      }
      theMatrix -> C[i][j] = sum;
    }
  }

	return NULL;

}

int main() {

	pthread_mutex_init(&mutex1, NULL);

	struct timeval start_time, stop_time, start_time2, stop_time2;
	long long total_time, test_time;

	int a_dim1 = 100;
	int a_dim2 = 100;
	int b_dim2 = 100;
	struct complex ** D;
	struct complex ** E;
	struct complex ** F;
	D = gen_random_matrix(a_dim1, a_dim2);
	E = gen_random_matrix(a_dim1, a_dim2);
	F = new_empty_matrix(a_dim1, a_dim2);
	
	int i;
	pthread_t thread_id[NTHREADS];
	int thread_args[NTHREADS];

	struct finalResult example;
	example.A = D;
	example.B = E;
	example.C = new_empty_matrix(a_dim1, a_dim2);
	example.a_dim1 = a_dim1;
	example.a_dim2 = a_dim2;
	example.b_dim2 = b_dim2;

	gettimeofday(&start_time, NULL);

	for (i=0; i < NTHREADS; i++) {
		pthread_create(&thread_id[i], NULL, matmul, &example);
	}

	for (i=0; i < NTHREADS; i++) {
		pthread_join(thread_id[i], NULL);
	}

	gettimeofday(&stop_time, NULL);
	total_time = time_diff(&start_time, &stop_time);

	// printf("\nexample.final_position = [ %d ]\n", example.final_position);
	printf("\n*** Total time = [ %lld microseconds ]\n\n", total_time);

	gettimeofday(&start_time2, NULL);
	// printf("\nHERE\n");
	matmulMain(D, E, F, a_dim1, a_dim2, b_dim2);
	// printf("\nHERE NOW\n");
	gettimeofday(&stop_time2, NULL);
	test_time = time_diff(&start_time2, &stop_time2);

	// printf("\nexample.final_position = [ %d ]\n", example.final_position);
	printf("\n*** Test time = [ %lld microseconds ]\n\n", test_time);

	// write_out(example.C, a_dim1, a_dim2);
	// printf("\n");
	// write_out(F, a_dim1, a_dim2);
	// printf("\n");

	free_matrix(D);
	free_matrix(E);
	free_matrix(F);
	free_matrix(example.C);

	return 0;
}