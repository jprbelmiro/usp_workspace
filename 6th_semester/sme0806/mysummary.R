mysummary <- function(data){
     # Extracting the informantion
    mean = mean(data)
    sd = sd(data)
    log10 = log10(data)
    standard = (dados - mean)/sd
    amp = c(min(dados),max(dados))
     
    # Returning the extracted information
    return(list("mean" = mean,"sd" = sd,"log10" = log10,"standard" = standard,"amp" = amp))
 }
