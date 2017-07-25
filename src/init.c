#include <R.h>                                                                                             
#include <Rinternals.h>                                                                                    
#include <stdlib.h> // for NULL                                                                            
#include <R_ext/Rdynload.h>                                                                                
                                                                                                           
/* FIXME:                                                                                                  
   Check these declarations against the C/Fortran source code.                                             
*/                                                                                                         

/* .Call calls */
extern SEXP libstableR_stable_cdf(SEXP, SEXP, SEXP, SEXP);
extern SEXP libstableR_stable_fit_init(SEXP, SEXP);
extern SEXP libstableR_stable_fit_koutrouvelis(SEXP, SEXP, SEXP);
extern SEXP libstableR_stable_fit_mle(SEXP, SEXP, SEXP);
extern SEXP libstableR_stable_fit_mle2d(SEXP, SEXP, SEXP);
extern SEXP libstableR_stable_pdf(SEXP, SEXP, SEXP, SEXP);
extern SEXP libstableR_stable_q(SEXP, SEXP, SEXP, SEXP);
extern SEXP libstableR_stable_rnd(SEXP, SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"libstableR_stable_cdf",              (DL_FUNC) &libstableR_stable_cdf,              4},
    {"libstableR_stable_fit_init",         (DL_FUNC) &libstableR_stable_fit_init,         2},
    {"libstableR_stable_fit_koutrouvelis", (DL_FUNC) &libstableR_stable_fit_koutrouvelis, 3},
    {"libstableR_stable_fit_mle",          (DL_FUNC) &libstableR_stable_fit_mle,          3},
    {"libstableR_stable_fit_mle2d",        (DL_FUNC) &libstableR_stable_fit_mle2d,        3},
    {"libstableR_stable_pdf",              (DL_FUNC) &libstableR_stable_pdf,              4},
    {"libstableR_stable_q",                (DL_FUNC) &libstableR_stable_q,                4},
    {"libstableR_stable_rnd",              (DL_FUNC) &libstableR_stable_rnd,              4},
    {NULL, NULL, 0}
};

void R_init_libstableR(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}

