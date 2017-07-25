\name{stable_fit}
\alias{stable_fit_init}
\alias{stable_fit_koutrouvelis}
\alias{stable_fit_mle}
\alias{stable_fit_mle2d}
\alias{libstableR_stable_fit_init}
\alias{libstableR_stable_fit_koutrouvelis}
\alias{libstableR_stable_fit_mle}
\alias{libstableR_stable_fit_mle2d}
\title{
  stable_fit: Methods for parameter estimation of skew stable distributions.
}
\description{
  A set of functions are provided that perform the parameter estimation of skew stable distributions with different methods.
}
\usage{
 
  stable_fit_init(rnd, parametrization = 0)

  stable_fit_koutrouvelis(rnd, pars_init, parametrization = 0)

  stable_fit_mle(rnd, pars_init, parametrization = 0)

  stable_fit_mle2d(rnd, pars_init, parametrization = 0)
}
\arguments{
  \item{rnd}{
    Random sample
  }
  \item{pars_init}{
    Vector with an initial estimation of the parameters. pars_init = c(alpha, beta, sigma, mu), where

      - alpha: shape / stability parameter, with 0 < alpha <= 2.
    
      - beta:  skewness parameter, with -1 <= beta <= 1.
      
      - sigma: scale parameter, with 0 < sigma.
      
      - mu:    location parameter, with mu real.
  }
  \item{parametrization}{
    Parametrization used for the skew stable distribution, as defined by JP Nolan (1997). By default, parametrization = 0.
  }
}
\details{
  stable_fit_init() uses McCulloch's method of quantiles [3]. This is usually a good initialization for the rest of the methods.

  stable_fit_koutrouvelis() implements Koutrouvellis' method based on the characteristic function [4].

  stable_fit_mle() implements a Maximum likelihood estimation.
  
  stable_fit_mle2() implements a modified maximum likelihood estimation as described in [1].
}
\value{
  A numeric vector.
}
\references{
  [1] Royuela-del-Val J, Simmross-Wattenberg F, Alberola López C (2017). libstable: Fast, Parallel and High-Precision Computation of alpha-stable Distributions in R, C/C++ and MATLAB. Journal of Statistical Software, 78(1), 1-25. doi:10.18637/jss.v078.i01
  
  [2] Chambers JM, Mallows CL, Stuck BW (1976). A Method for Simulating Stable Random Variables. Journal of the American Statistical Association, 71(354), 340-344. doi:10.1080/01621459.1976.10480344.
  
  [3] McCulloch JH (1986). Simple Consistent Estimators of Stable Distribution Parameters. Communications in Statistics - Simulation and Computation, 15(4), 1109-1136. doi:10.1080/03610918608812563.
  
  [4] Koutrouvelis IA (1981). An Iterative Procedure for the Estimation of the Parameters of Stable Laws. Communications in Statistics - Simulation and Computation, 10(1), 17-28. doi:10.1080/03610918108812189.
  
  [5] Nolan JP (1997). Numerical Calculation of Stable Densities and Distribution Functions. Stochastic Models, 13(4) 759-774. doi:10.1080/15326349708807450.
}
\author{
Javier Royuela del Val, Federico Simmross Wattenberg and Carlos Alberola López

Maintainer: Javier Royuela del Val <jroyval@lpi.tel.uva.es>
}
\examples{
  # Set alpha, beta, sigma and mu stable parameters in a vector
  pars <- c(1.5, 0.9, 1, 0)
 
  # Generate 300 random values
  rnd <- stable_rnd(300, pars)
  
  # Estimate the parameters of the skew stable distribution given
  # the generated sample:

  # Using the McCulloch's estimator:
  pars_init <- stable_fit_init(rnd)
  
  # Using the Koutrouvelis' estimator, with McCulloch estimation
  # as a starting point:
  pars_est_K <- stable_fit_koutrouvelis(rnd, pars_init)
  
  # Using maximum likelihood estimator:
  # pars_est_ML <- stable_fit_mle(rnd, pars_est_K)
  
  # Using modified maximum likelihood estimator (see [1]):
  # pars_est_ML2 <- stable_fit_mle2d(rnd, pars_est_K)
}

\keyword{distribution}
