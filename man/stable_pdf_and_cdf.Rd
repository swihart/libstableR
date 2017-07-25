\name{stable_pdf_and_cdf}
\alias{stable_pdf}
\alias{stable_cdf}
\alias{libstableR_stable_pdf}
\alias{libstableR_stable_cdf}
\title{
stable_pdf/stable_cdf: PDF and CDF of a skew stable distribution.
}
\description{
    Evaluate the PDF or the CDF of the skew stable distribution with parameters
    pars = c(alpha, beta, sigma, mu) at the points given in x.

    _parametrization_ argument specifies the parametrization used for the distribution
    as described by JP Nolan (1997). The default value is _parametrization_ = 0.

    _tol_ sets the relative error tolerance (precision) to _tol_. The default value
    is tol = 1e-12.
}
\usage{
  stable_pdf(x, pars, parametrization = 0, tol = 1e-12)
  stable_cdf(x, pars, parametrization = 0, tol = 1e-12)
}
\arguments{
  \item{x}{
    Vector of points where the pdf will be evaluated.
    }
  \item{pars}{
    Vector of skew stable distribution parameters
    pars = c(alpha, beta, sigma, mu), where

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
    Relative error tolerance (precision) of the calculated values. By
    default, tol = 1e-12.
  }
}
\value{
  A numeric vector.
}
\references{
Nolan JP (1997). Numerical Calculation of Stable Densities and Distribution
    Functions. Stochastic Models, 13(4) 759-774.
}
\author{
Javier Royuela del Val, Federico Simmross Wattenberg and Carlos Alberola López

Maintainer: Javier Royuela del Val <jroyval@lpi.tel.uva.es>
}
\examples{
  pars <- c(1.5, 0.9, 1, 0)
  x <- seq(-5, 10, 0.001)
  
  pdf <- stable_pdf(x, pars)
  cdf <- stable_cdf(x, pars)
  
  plot(x, pdf, type = "l")
}
\keyword{distribution}
