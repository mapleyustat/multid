BlockTriMatrix::~BlockTriMatrix(void)
{
}

void
solve(BlockTriMatrix &M, BlockTriVector &x, BlockTriVector &y)
{
	int i;
	int n_eqn = M.n_eqn();
	MatrixNArray &U = M.upper_diagonal();
	MatrixNArray &D = M.diagonal();
	MatrixNArray &L = M.lower_diagonal();

	for (i = 0; i < n_eqn-1; i++) {
		FactorMatrixN F(factor(D(i)));

		U(i+1) = solve(F, U(i+1));
		D(i+1) -= L(i)*U(i+1);

		y(i) = solve(F, y(i));
		y(i+1) -= L(i)*y(i);
	}

	FactorMatrixN G(factor(D(n_eqn-1)));
	x(n_eqn-1) = solve(G, y(n_eqn-1));
	for (i = n_eqn-2; i >= 0; i--)
		x(i) = y(i) - U(i+1)*x(i+1);
}

void
solve_periodic(BlockTriMatrix &M, BlockTriVector &x, BlockTriVector &y)
{
	int i;
	int n_eqn = M.n_eqn();
	MatrixNArray &U = M.upper_diagonal();
	MatrixNArray &D = M.diagonal();
	MatrixNArray &L = M.lower_diagonal();

	MatrixN A(L(n_eqn-1));
	for (i = 0; i < n_eqn-2; i++) {
		FactorMatrixN F(factor(D(i)));

		U(i+1) = solve(F, U(i+1));
		D(i+1) -= L(i)*U(i+1);

		y(i) = solve(F, y(i));
		y(i+1) -= L(i)*y(i);

		MatrixN L_tmp(L(i));
		L(i) = solve(F, A);
		A = -1.*(L_tmp*L(i));
	}
	A += U(n_eqn-1);
	FactorMatrixN F(factor(D(n_eqn-2)));
	y(n_eqn-2) = solve(F, y(n_eqn-2));
	A = solve(F, A);

	MatrixN B(U(0));
	for (i = 0; i < n_eqn-2; i++) {
		y(n_eqn-1) -= B*y(i);
		D(n_eqn-1) -= B*L(i);
		B = -1.*B*U(i+1);
	}
	B += L(n_eqn-2);
	y(n_eqn-1) -= B*y(n_eqn-2);
	D(n_eqn-1) -= B*A;

	FactorMatrixN G(factor(D(n_eqn-1)));
	x(n_eqn-1) = solve(G, y(n_eqn-1));
	x(n_eqn-2) = y(n_eqn-2) - A*x(n_eqn-1);
	for (i = n_eqn-3; i >= 0; i--)
		x(i) = y(i) - U(i+1)*x(i+1) - L(i)*x(n_eqn-1);
}

void
solve_lower(BlockTriMatrix &M, BlockTriVector &x, BlockTriVector &y)
{
	int n_eqn = M.n_eqn();
	MatrixNArray &D = M.diagonal();
	MatrixNArray &L = M.lower_diagonal();
	MatrixNArray &LL = M.lower_lower_diagonal();

	FactorMatrixN F(factor(D(0)));
	x(0) = solve(F, y(0));

	if (n_eqn == 1)
		return;

	FactorMatrixN G(factor(D(1)));
	x(1) = solve(G, y(1) - L(0)*x(0));

	for (int i = 2; i < n_eqn; i++) {
		FactorMatrixN H(factor(D(i)));
		x(i) = solve(H, y(i) - LL(i-2)*x(i-2) - L(i-1)*x(i-1));
	}
}
