#include "measurement.h"
#include <math.h>
float energy_rms(const float *s,size_t n){if(!s||!n)return 0.0f;double x=0;for(size_t i=0;i<n;i++)x+=(double)s[i]*s[i];return(float)sqrt(x/n);}
float energy_apparent_power(float v,float i){return v*i;}
float energy_active_power(float s,float pf){if(pf<0)pf=0;if(pf>1)pf=1;return s*pf;}
float energy_accumulate_wh(float e,float p,float dt){return dt>0?e+p*dt/3600.0f:e;}
void energy_build_measurement(const float*v,const float*i,size_t n,float pf,float prev,float dt,const measurement_limits_t*l,uint32_t seq,energy_measurement_t*out){
if(!out)return;out->voltage_rms_v=energy_rms(v,n);out->current_rms_a=energy_rms(i,n);out->apparent_power_va=energy_apparent_power(out->voltage_rms_v,out->current_rms_a);out->active_power_w=energy_active_power(out->apparent_power_va,pf);out->power_factor=pf;out->energy_wh=energy_accumulate_wh(prev,out->active_power_w,dt);out->sample_count=seq;out->alarm_flags=0;if(l){if(out->voltage_rms_v>l->voltage_limit_v)out->alarm_flags|=1u;if(out->current_rms_a>l->current_limit_a)out->alarm_flags|=2u;}}