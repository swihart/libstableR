/* stable_R.cpp
 *
 * R wrappers
 *
 *
 * Copyright (C) 2015. Javier Royuela del Val
 *                     Federico Simmross Wattenberg
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; If not, see <http://www.gnu.org/licenses/>.
 *
 *
 *  Javier Royuela del Val.
 *  E.T.S.I. Telecomunicación
 *  Universidad de Valladolid
 *  Paseo de Belén 15, 47002 Valladolid, Spain.
 *  jroyval@lpi.tel.uva.es
 */

/*
* Check input parameters
*/

#include <Rcpp.h>

using namespace Rcpp;

/* Libstable is writen in C, so we need to make then callable from C++ */
extern "C" {
  #include "stable.h"
}

int checkParams(NumericVector& pars, int parametrization)
{
  int out = 0;

  if (parametrization < 0 || parametrization > 1) {
    perror("Only parametrizations 0 and 1 are accepted");
    out = 5;
  }

  if (pars.size() < 1)
    pars.push_back(2.0); /* alpha */
  else if (pars[0] < 0 || pars[0] > 2.0) {
    perror("Alpha must be between 0.0 and 2.0");
    out = 1;
  }

  if (pars.size() < 2)
    pars.push_back(0.0); /* beta  */
  else if (pars[1] < -1.0 || pars[1] > 1.0) {
    perror("Beta must be between -1.0 and 1.0");
    out = 2;
  }

  if (pars.size() < 3)
    pars.push_back(1.0); /* sigma */
  else if (pars[2] <= 0.0) {
    perror("Sigma must be greater than 0.0");
    out = 3;
  }

  if (pars.size() < 4)
    pars.push_back(0.0); /* mu    */

  return out;
}

/*
* Get stable distribution parameters
*/
NumericVector getPars(StableDist *dist, int parametrization = 0)
{
  NumericVector pars(4);
  pars[0] = dist->alpha;
  pars[1] = dist->beta;
  pars[2] = dist->sigma;
  if (parametrization == 0)
      pars[3] = dist->mu_0;
  else
      pars[3] = dist->mu_1;

  return pars;
}

// [[Rcpp::export]]
NumericVector stable_pdf(NumericVector x, NumericVector pars, int parametrization=0, double tol=1e-12)
{
  NumericVector out(x.size());

  if(checkParams(pars, parametrization) != 0) {
    perror("No valid parameters provided");
    out.fill(NA_REAL);
    return out;
  }

  StableDist * dist = stable_create(pars[0], pars[1], pars[2], pars[3], parametrization);
  stable_set_relTOL(tol);
  stable_pdf(dist, &(x[0]), x.size(), &(out[0]), NULL);
  stable_free(dist);

  return out;
}

// [[Rcpp::export]]
NumericVector stable_cdf(NumericVector x, NumericVector pars, int parametrization=0, double tol=1e-12)
{
  NumericVector out(x.size());

  if(checkParams(pars, parametrization) != 0) {
    perror("No valid parameters provided");
    out.fill(NA_REAL);
    return out;
  }

  StableDist * dist = stable_create(pars[0], pars[1], pars[2], pars[3], parametrization);
  stable_set_relTOL(tol);
  stable_cdf(dist, &(x[0]), x.size(), &(out[0]), NULL);
  stable_free(dist);

  return out;
}

// [[Rcpp::export]]
NumericVector stable_q(NumericVector p, NumericVector pars, int parametrization=0, double tol=1e-12)
{
  NumericVector out(p.size());

  if(checkParams(pars, parametrization) != 0) {
    perror("No valid parameters provided");
    out.fill(NA_REAL);
    return out;
  }

  int k = 0;
  int N = p.size();
  for (k = 0; k < N; k++) {
    if (p[k]>1 || p[k]<0) {
      perror("p but must be between 0 and 1");
      out.fill(NA_REAL);
      return out;
    }
  }

  StableDist * dist = stable_create(pars[0], pars[1], pars[2], pars[3], parametrization);
  stable_set_relTOL(tol);
  stable_q(dist, &(p[0]), p.size(), &(out[0]), NULL);
  stable_free(dist);

  return out;
}

// [[Rcpp::export]]
NumericVector stable_rnd(int N, NumericVector pars, int parametrization=0, int seed=0)
{
  NumericVector out(N);

  if(checkParams(pars, parametrization) != 0) {
    perror("No valid parameters provided");
    out.fill(NA_REAL);
    return out;
  }

  StableDist * dist = stable_create(pars[0], pars[1], pars[2], pars[3], parametrization);
  if (seed != 0) {
    stable_rnd_seed(dist, seed);
  }
  stable_rnd(dist, &(out[0]), N);
  stable_free(dist);

  return out;
}

// [[Rcpp::export]]
NumericVector stable_fit_init(NumericVector rnd, int parametrization=0)
{
  /* Non an iterative method. Parameters do not influence the result */
  StableDist* dist = stable_create(2.0, 0.0, 1.0, 0.0, 0);
  stable_fit_init(dist, &(rnd[0]), rnd.size(), NULL, NULL);

  NumericVector out = getPars(dist, parametrization);

  stable_free(dist);
  return out;
}

// [[Rcpp::export]]
NumericVector stable_fit_koutrouvelis(NumericVector rnd, NumericVector pars_init = NumericVector::create(), int parametrization=0)
{
  if (pars_init.size() == 0)
    pars_init <- stable_fit_init(rnd, parametrization);
    
  if(checkParams(pars_init, parametrization) != 0) {
    perror("No valid parameters provided");
    NumericVector out(4, NA_REAL);
    return out;
  }

  StableDist* dist = stable_create(pars_init[0], pars_init[1], pars_init[2], pars_init[3], parametrization);

  
  if (stable_fit_koutrouvelis(dist, &(rnd[0]), rnd.size()) < 0) {
      Rprintf("Stable_fit_koutrouvelis error");
  }

  NumericVector out = getPars(dist, parametrization);

  stable_free(dist);
  return out;
}

// [[Rcpp::export]]
NumericVector stable_fit_mle(NumericVector rnd, NumericVector pars_init = NumericVector::create(), int parametrization = 0)
{
  
  if (pars_init.size() == 0) {
    pars_init <- stable_fit_init(rnd, parametrization);
    Rprintf("INIT MCCULLCOH\n");
  }
  else {
    Rprintf("SKIP INIT\n");
  }
    
  if(checkParams(pars_init, parametrization) != 0) {
    perror("No valid parameters provided");
    NumericVector out(4, NA_REAL);
    return out;
  }

  StableDist* dist = stable_create(pars_init[0], pars_init[1], pars_init[2], pars_init[3], parametrization);
  
  if (stable_fit_mle(dist, &(rnd[0]), rnd.size()) < 0) {
      Rprintf("Stable_fit_mle error");
  }

  NumericVector out = getPars(dist, parametrization);

  stable_free(dist);
  return out;
}

// [[Rcpp::export]]
NumericVector stable_fit_mle2d(NumericVector rnd, NumericVector pars_init = NumericVector::create(), int parametrization = 0)
{
  
  if (pars_init.size() == 0)
    pars_init <- stable_fit_init(rnd, parametrization);
    
  if(checkParams(pars_init, parametrization) != 0) {
    perror("No valid parameters provided");
    NumericVector out(4, NA_REAL);
    return out;
  }

  StableDist* dist = stable_create(pars_init[0], pars_init[1], pars_init[2], pars_init[3], parametrization);
  stable_fit_mle2d(dist, &(rnd[0]), rnd.size());

  NumericVector out = getPars(dist, parametrization);

  stable_free(dist);
  return out;
}
