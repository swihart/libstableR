
<!-- README.md is generated from README.Rmd. Please edit that file -->
[![Travis-CI Build Status](https://travis-ci.org/hrbrmstr/libstableR.svg?branch=master)](https://travis-ci.org/hrbrmstr/libstableR) [![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/github/hrbrmstr/libstableR?branch=master&svg=true)](https://ci.appveyor.com/project/hrbrmstr/libstableR)

libstableR
==========

Fast and Accurate Evaluation, Random Number Generation and Parameter Estimation of Skew Stable Distributions

`libstableR` provides functions to work with skew stable distributions in a fast and accurate way. It performs:

-   Fast and accurate evaluation of the probability density function (PDF) and cumulative density function (CDF).
-   Fast and accurate evaluation of the quantile function (CDF^{-1}).
-   Random numbers generation.
-   Skew stable parameter estimation with:
    -   McCulloch's method of quantiles.
    -   Koutrouvellis' method.
    -   Maximum likelihood estimation.
    -   Modified maximum likelihood estimation.
-   The evaluation of the PDF and CDF is based on the formulas provided by John P Nolan.

Authors
-------

-   Javier Royuela del Val <jroyval@@lpi.tel.uva.es> (Maintainer)
-   Federico Simmross Wattenberg
-   Carlos Alberola López

(I just rounded out some corners and added macOS compatiblity)

What's in the tin?
------------------

-   `stable_cdf`: PDF and CDF of a skew stable distribution.
-   `stable_fit`: Methods for parameter estimation of skew stable distributions.
-   `stable_fit_init`: Methods for parameter estimation of skew stable distributions.
-   `stable_fit_koutrouvelis`: Methods for parameter estimation of skew stable distributions.
-   `stable_fit_mle`: Methods for parameter estimation of skew stable distributions.
-   `stable_fit_mle2d`: Methods for parameter estimation of skew stable distributions.
-   `stable_pdf`: PDF and CDF of a skew stable distribution.
-   `stable_pdf_and_cdf`: PDF and CDF of a skew stable distribution.
-   `stable_q`: Quantile function of skew stable distributions
-   `stable_rnd`: Skew stable distribution random sample generation.

Usage
-----

``` r
# devtools::install_github("hrbrmstr/libstableR") # macOS compatibility
# install.packages("libstableR") # macOS compat not on CRAN yet

library(libstableR)

# Set alpha, beta, sigma and mu stable parameters in a vector
pars <- c(1.5, 0.9, 1, 0)

# Generate an abscissas axis and probabilities vector
x <- seq(-5, 10, 0.05)
p <- seq(0.01, 0.99, 0.01)

# Calculate pdf, cdf and quantiles
pdf <- stable_pdf(x, pars)
head(pdf)
#> [1] 0.0006156733 0.0006353004 0.0006559238 0.0006776202 0.0007004754
#> [6] 0.0007245854

cdf <- stable_cdf(x, pars)
head(cdf)
#> [1] 0.001808881 0.001840151 0.001872428 0.001905762 0.001940209 0.001975830

xq  <- stable_q(p, pars)
head(xq)
#> [1] -2.662445 -2.282506 -2.070792 -1.918121 -1.796182 -1.693242

# Generate 300 random values
rnd <- stable_rnd(300, pars)
head(rnd)
#> [1] 79.6139859 -1.7023197 -0.8170737  6.0255344  0.1403793  1.6730137

# Estimate the parameters of the skew stable distribution given
# the generated sample:

# Using the McCulloch's estimator:
pars_est_M <- stable_fit_init(rnd)
head(pars_est_M)
#> [1] 1.35696331 0.66541472 0.95827920 0.03719542

# Using the Koutrouvelis' estimator:
pars_est_K <- stable_fit_koutrouvelis(rnd, pars_est_M)
head(pars_est_K)
#> [1]  1.38704434  0.88882173  0.96496141 -0.09001025
```

``` r
alpha <- 1.25;  # stability index
beta  <- 0.95;  # skew index
sigma <- 2.0;   # scale parameter
mu    <- 0.0;   # location parameter

pars <- c(alpha, beta, sigma, mu)

# abscissae vector
x    <- seq(from=-5, to=100, by=0.1)

# evaluation of pdf and cdf
pdf  <- stable_pdf(x, pars, parametrization=0, tol=1e-12)
cdf  <- stable_cdf(x, pars, parametrization=0, tol=1e-12)

# probabilities vector and quantile function evaluation
p  <- seq(from=0.01, to=0.99, by=0.01)
q  <- stable_q(p, pars, parametrization=0, tol=1e-12)

# Random numbers generation
N   <- 300;
rnd <- stable_rnd(N, pars, seed=1234)

# Parameter estimation with Koutrouvelis method.
# McCulloch estimator will be used for initialization.
pars_init <- stable_fit_init(rnd)
pars_K    <- stable_fit_koutrouvelis(rnd, pars_init)

# Get the pdf given by the estimated parameters
pdf_init <- stable_pdf(x, pars_init)
pdf_K    <- stable_pdf(x, pars_K)

# Plot histogram, true pdf and pdf from the estimated parameters
xlim <- c(-5, 30)
ylim <- c(0, 0.15)
breaks <- seq(min(rnd)-1, max(rnd)+1, 0.5);
hist(rnd, breaks=breaks, freq=FALSE, xlim=xlim, ylim=ylim)

lines(x, pdf, col = "red", lwd=2)
lines(x, pdf_init, col = "green", lwd=2)
lines(x, pdf_K, col = "blue", lwd=2)

legend(20, 0.15,
       c("Histogram", "True pdf", "McCulloch", "Koutrouveils"),#,"Max. likelihood"),
       lty = c(1,1,1,1,1),
       lwd = c(2,2,2,2,2),
       col=c("black","red","green","blue"))#,"yellow"))
```

<img src="README-plot-1.png" width="672" />
