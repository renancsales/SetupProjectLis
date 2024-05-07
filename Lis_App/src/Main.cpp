#include "lis.h"

// Based on lis example (test4.c)
int main(LIS_INT argc, char* argv[])
{
	// Set variables
	LIS_INT i, n, gn, is, ie, iter;
	LIS_MATRIX A;
	LIS_VECTOR b, x;
	LIS_SOLVER solver;

	// Initialize and allocate
	n = 100;
	lis_initialize(&argc, &argv);

	lis_matrix_create(LIS_COMM_WORLD, &A);
	lis_matrix_set_size(A, 0, n);
	lis_matrix_get_size(A, &n, &gn);
	lis_matrix_get_range(A, &is, &ie);
		for (i = is; i < ie; i++)
		{
			if (i > 0) lis_matrix_set_value(LIS_INS_VALUE, i, i - 1, -1.0, A);
			if (i < gn - 1) lis_matrix_set_value(LIS_INS_VALUE, i, i + 1, -1.0, A);
			lis_matrix_set_value(LIS_INS_VALUE, i, i, 2.0, A);
		}
	lis_matrix_set_type(A, LIS_MATRIX_CSR);
	lis_matrix_assemble(A);

	lis_vector_create(0, &b);
	lis_vector_set_size(b, 0, n);
	//lis_vector_set_all(1.0, b);
	lis_vector_set_value(LIS_INS_VALUE, 0, -1, b);
	lis_vector_set_value(LIS_INS_VALUE, n-1,1, b);

	lis_vector_create(0, &x);
	lis_vector_set_size(x, 0, n);
	lis_vector_set_all(0.0, x);

	
	lis_vector_print(b);

	// Set solver options
	lis_solver_create(&solver);
	lis_solver_set_option("-i bicgstab -p none", solver);
	lis_solver_set_option("-tol 1.0e-10 -maxiter 100", solver);
	lis_solver_set_option("-print 2", solver);
	lis_solver_set_option("-omp_num_threads 10", solver);

	// Solve
	lis_solve(A, b, x, solver);
	lis_solver_get_iter(solver, &iter);
	printf("number of iterations = %d\n", iter);
	lis_vector_print(x);
	// Release memory
	lis_matrix_destroy(A);
	lis_vector_destroy(b);
	lis_vector_destroy(x);
	lis_solver_destroy(solver);
	//End
	lis_finalize();
	return 0;
}

