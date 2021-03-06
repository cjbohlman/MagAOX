/** \file timespecX.hpp 
  * \brief A fixed-width timespec structure and utilities.
  * \author Jared R. Males (jaredmales@gmail.com)
  *
  * \ingroup flatlogs_files
  * 
  * History:
  * - 2017-06-27 created by JRM
  * - 2018-08-17 moved to flatlogs
  */ 

#ifndef flatlogs_timespecX_hpp
#define flatlogs_timespecX_hpp

#include <cstdint>

#include "logDefs.hpp"

namespace flatlogs
{

///A fixed-width timespec structure.
/** To ensure that binary encoding of time is stable regardless of environment, we use a custom timespec
  * composed of fixed-width types.
  * 
  * \note This is NOT binary compatible with plain timespec.  Use the provided conversions.
  * 
  * \ingroup flatlogs_time
  * 
  */
struct timespecX 
{
   secT time_s; ///< Time since the Unix epoch
   nanosecT time_ns; ///< Nanoseconds.  


   ///Convert a native timespec to a timespecX.
   /**
     * \returns this reference, if values are 0 and 0 then the input was too big or negative. 
     */
   timespecX & operator=( const timespec & ts /**< [in] the native timespec from which to get values */)
   {
      if(ts.tv_sec < 0 || ts.tv_sec > 4294967295) ///\todo make this use minval and maxval
      {
         time_s = 0;
         time_ns = 0;
      }
      else 
      {
         time_s = ts.tv_sec;
         time_ns = ts.tv_nsec;
      }
      
      return *this;
   }
   
   ///Get a native timespec from this custom one.
   timespec getTimespec()
   {
      struct timespec ts;
      
      ts.tv_sec = time_s;
      ts.tv_nsec = time_ns;
      
      return ts;
   }
   
   ///Fill the the timespecX with the current time.
   /** This is based on the usual clock_gettime.  clockid_t is a template parameter 
     * since we probaby always want CLOCK_REALTIME, but if we don't for some reason
     * it will be passed in the same order as in clock_gettime.
     * 
     * \tparam clk_id specifies the type.
     */ 
   template<clockid_t clk_id=CLOCK_REALTIME>
   void gettime()
   {
      struct timespec ts;
      clock_gettime(clk_id, &ts);
      (*this) = ts; //see operator=
   }
   
   ///Get the filename timestamp for this timespecX.
   /** Fills in a string with the timestamp encoded as
     * \verbatim
       YYYYMMDDHHMMSSNNNNNNNNN
       \endverbatim
     *
     */ 
   int timeStamp(std::string & tstamp /**< [out] the string to hold the formatted time */)
   {
      tm uttime;//The broken down time.
   
      time_t t0 = time_s;

      if(gmtime_r(&t0, &uttime) == 0)
      {
         std::cerr << "Error getting UT time (gmtime_r returned 0). At: " <<  __FILE__ << " " << __LINE__ << "\n";
         return -1;
      }
   
      char buffer[24];

      snprintf(buffer, 24, "%04i%02i%02i%02i%02i%02i%09i", uttime.tm_year+1900, uttime.tm_mon+1, uttime.tm_mday, uttime.tm_hour, uttime.tm_min, uttime.tm_sec, static_cast<int>(time_ns)); //casting in case we switch type of time_ns.
   
      tstamp = buffer;

      return 0;   
   }
   
    ///Get the filname timestamp for this timespecX.
   /** Returns a string with the timestamp encoded as
     * \verbatim
       YYYYMMDDHHMMSSNNNNNNNNN
       \endverbatim
     *
     */ 
   std::string timeStamp()
   {
      std::string tstamp;
      timeStamp(tstamp);
      return tstamp;
   }
   
   /// Get a date-time string in ISO 8601 format for timespecX
   /** Returns a string in the ISO 8601 format:
     * \verbatim
       YYYY-MM-DDTHH:MM:SS.SSSSSSSSS
       \endverbatim
     *
     *
     * \retval std::string containing the formated date/time 
     * 
     */ 
   std::string ISO8601DateTimeStrX()
   {
      tm bdt; //broken down time
      time_t tt = time_s;
      gmtime_r( &tt, &bdt);
      
      char tstr1[25];
      
      strftime(tstr1, 25, "%FT%H:%M:%S", &bdt);
      
      char tstr2[11];
      
      snprintf(tstr2, 11, ".%09i", static_cast<int>(time_ns)); //casting in case we switch to int64_t
      
      return std::string(tstr1) + std::string(tstr2);
   }
} __attribute__((packed));

///Convert a timespecX to a native timespec
/**
  * \ingroup flatlogs_time
  */ 
inline
void timespecFromX ( timespec & ts, ///< [out] the native timespec to set
                     const timespecX & tsX ///< [in] the fixed-width timespec from which to get values
                   ) 
{
   ts.tv_sec = tsX.time_s;
   ts.tv_nsec = tsX.time_ns;
   
}

///Fill in a timespecX with the current time.
/** This is based on the usual clock_gettime.  clockid_t is a template parameter 
  * since we probaby always want CLOCK_REALTIME, but if we don't for some reason
  * it will be passed in the same order as in clock_gettime.
  * 
  * \tparam clk_id specifies the type.
  * 
  * \ingroup flatlogs_time
  * 
  */ 
template<clockid_t clk_id=CLOCK_REALTIME>
void clock_gettimeX( timespecX & tsX /**< [out] the fixed-width timespec to populate */)
{
   tsX.gettime<clk_id>();
}

}//namespace flatlogs


#endif //flatlogs_timespecX_hpp

