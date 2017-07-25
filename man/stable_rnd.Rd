\name{stable_rnd}
\alias{stable_rnd}
\alias{libstableR_stable_rnd}

\title{
  stable_rnd: Skew stable distribution random sample generation.
}
\description{
  stable_rnd(N, pars) generates N random samples of a skew stable distribuiton
  with parameters pars = c(alpha, beta, sigma, mu) using the Chambers, Mallows,
  and Stuck (1976) method.
  
  The random number generator seed is set to the _seed_ argument before execution.
  If _seed_ = 0, the system time is used.
}
\usage{
  stable_rnd(N, pars, parametrization = 0, seed = 0)
}
\arguments{
  \item{N}{
    Number of values to generate.
  }
  \item{pars}{
    Vector of skew stable distribution parameters pars = c(alpha, beta, sigma, mu), where

      - alpha: shape / stability parameter, with 0 < alpha <= 2.
    
      - beta:  skewness parameter, with -1 <= beta <= 1.
      
      - sigma: scale parameter, with 0 < sigma.
      
      - mu:    location parameter, with mu real.
  }
  \item{parametrization}{
    Parametrization used for the skew stable distribution, as defined by JP Nolan (1997). By default, parametrization = 0.
  }
   
  \item{seed}{
    Seed used to initialize the internal random numbers generators. If not provided, it is set by default to the system time. By default, seed = 0.
  }
}
\value{
  A numeric vector.
}
\references{
Chambers JM, Mallows CL, Stuck BW (1976). A Method for Simulating Stable Random Variables. Journal of the American Statistical Association, 71(354), 340-344. doi:10.1080/01621459.1976.10480344.
}
\author{
Javier Royuela del Val, Federico Simmross Wattenberg and Carlos Alberola López

Maintainer: Javier Royuela del Val <jroyval@lpi.tel.uva.es>
}
\examples{

N <- 1000
pars <- c(1.25, 0.95, 1.0, 0.0)
rnd <- stable_rnd(N, pars)

hist(rnd)
}
\keyword{distribution}
