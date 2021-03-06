#include "Util.h" 
#include "UsefulAdu5Pat.h" 
#include "RawAnitaHeader.h" 
#include "AnalysisConfig.h" 

/* nothing to see here, please move along */ 


static const UCorrelator::AnalysisConfig defaultConfig;

static const double  C_in_m_ns = 0.299792;


double UCorrelator::getWAISDt(const UsefulAdu5Pat * pat, const RawAnitaHeader * hdr, AnitaPol::AnitaPol_t pol, const AnalysisConfig * cfg, double * distance)
{

  if (!cfg) cfg = &defaultConfig; 

  double time_to_wais = ((UsefulAdu5Pat*) pat)->getWaisDivideTriggerTimeNs(); 
  if (distance) *distance = time_to_wais * C_in_m_ns; 
  unsigned trig_time = hdr->triggerTimeNs; 
  return trig_time + (pol == AnitaPol::kHorizontal ? cfg->wais_hpol : cfg->wais_vpol).GPS_offset- time_to_wais; 
}

double UCorrelator::getLDBDt(const UsefulAdu5Pat * pat, const RawAnitaHeader * hdr, AnitaPol::AnitaPol_t pol, const AnalysisConfig * cfg, double * distance)
{

  if (!cfg) cfg = &defaultConfig; 

  double time_to_ldb = ((UsefulAdu5Pat*) pat)->getLDBTriggerTimeNs(); 
  if (distance) *distance = time_to_ldb * C_in_m_ns; 
  unsigned trig_time = hdr->triggerTimeNs; 
  return trig_time + (pol == AnitaPol::kHorizontal ? cfg->ldb_hpol : cfg->ldb_vpol).GPS_offset- time_to_ldb; 
}

bool UCorrelator::isWAISVPol(const UsefulAdu5Pat * pat, const RawAnitaHeader * hdr, const AnalysisConfig * cfg )  
{

  if (!cfg) cfg = &defaultConfig; 

  double distance; 
  double dt = getWAISDt(pat,hdr, AnitaPol::kVertical, cfg,&distance); 
  if (distance > cfg->wais_vpol.max_distance) return false; 
  if (fabs(dt) > cfg->wais_vpol.max_dt) return false; 

  return true; 
}

bool UCorrelator::isWAISHPol(const UsefulAdu5Pat * pat, const RawAnitaHeader * hdr, const AnalysisConfig * cfg )  
{
  if (!cfg) cfg = &defaultConfig; 

  double distance; 
  double dt = getWAISDt(pat,hdr, AnitaPol::kHorizontal, cfg,&distance); 

//  printf("dt: %f; distance: %f\n", dt, distance); 
  if (distance > cfg->wais_hpol.max_distance) return false; 
  if (fabs(dt) > cfg->wais_hpol.max_dt) return false; 

  return true; 
}


bool UCorrelator::isLDBVPol(const UsefulAdu5Pat * pat, const RawAnitaHeader * hdr, const AnalysisConfig * cfg )  
{
  if (!cfg) cfg = &defaultConfig; 

  double distance; 
  double dt = getLDBDt(pat,hdr, AnitaPol::kVertical, cfg,&distance); 
  if (distance > cfg->ldb_vpol.max_distance) return false; 
  if (fabs(dt) > cfg->ldb_vpol.max_dt) return false; 

  return true; 
}

bool UCorrelator::isLDBHPol(const UsefulAdu5Pat * pat, const RawAnitaHeader * hdr, const AnalysisConfig * cfg )  
{
  if (!cfg) cfg = &defaultConfig; 

  double distance; 
  double dt = getLDBDt(pat,hdr, AnitaPol::kHorizontal, cfg,&distance); 
  if (distance > cfg->ldb_hpol.max_distance) return false; 
  if (fabs(dt) > cfg->ldb_hpol.max_dt) return false; 
  return true; 
}




