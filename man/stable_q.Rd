\name{stable_q}
\alias{stable_q}
\alias{libstableR_stable_q}

\title{
stable_q: quantile function of skew stable distributions
}
\description{
    Evaluate the quantile function (CDF^-1) of the skew stable distribution
    with parameters pars = c(alpha, beta, sigma, mu) at the points given in p.
    
    _parametrization_ argument specifies the parametrization used for the distribution
    as described by JP Nolan (1997). The default value is _parametrization_ = 0.

    _tol_ sets the relative error tolerance (precission) to _tol_. The default value
    is tol = 1e-12.
}
\usage{
stable_q(p, pars, parametrization = 0, tol = 1e-12)
}
\arguments{
  \item{p}{
    Vector of points where the quantile function will be evaluated, with  0 < p[i] < 1.0
    }
  \item{pars}{
    Vector of skew stable distribution parameters pars = c(alpha, beta, sigma, mu), where

      - alpha: shape / stability parameter, with 0 < alpha <= 2.
    
      - beta:  skewness parameter, with -1 <= beta <= 1.
      
      - sigma: scale parameter, with 0 < sigma.
      
      - mu:    location parameter, with mu real.
  }
  \item{parametrization}{
    Parametrization used for the skew stable distribution, as defined by
    JP Nolan (1997). By default, parametrization = 0.
  }
    
  \item{tol}{
    Relative error tolerance (precission) of the calculated values. By
    default, tol = 1e-12.
  }

}
\value{
  A numeric vector.
}
\author{
Javier Royuela del Val, Federico Simmross Wattenberg and Carlos Alberola López

Maintainer: Javier Royuela del Val <jroyval@lpi.tel.uva.es>
}
\keyword{distribution}
