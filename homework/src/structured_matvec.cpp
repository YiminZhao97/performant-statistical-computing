#include <Rcpp.h>
using Rcpp::NumericVector;
using Rcpp::NumericMatrix;

// [[Rcpp::export]]
NumericVector ar_precision_matvec(const NumericVector& v, double auto_corr) {
	int n = v.size();
	NumericVector result(n); // Allocate return vector
	double auto_corr_sq = pow(auto_corr, 2.); // '^' operator would not work
  // Fill in; remember that C array index starts from *0 instead of 1*
    result = (1 + auto_corr_sq) * v;
    result[0] = v[1];
    result[n - 1] = v[n - 1];
    
    for(int i = 0; i < n - 1; i++){
        result[i] = result[i] - auto_corr * v[i + 1];
    }
    for(int i = 0; i < n - 1; i++){
        result[i + 1] = result[i + 1] - auto_corr * v[i];
    }

    result = result / (1 - auto_corr_sq);
	return result;
}

