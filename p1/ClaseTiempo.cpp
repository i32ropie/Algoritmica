/*!a pesar de que se puede trabajar con nanosegundos, se devuelven los tiempos en microsegundos*/

// http://man7.org/linux/man-pages/man2/clock_gettime.2.html
/*
Data Type: struct timespec

    The struct timespec structure represents an elapsed time. It is declared in sys/time.h and has the following members:

    time_t tv_sec
       This represents the number of whole seconds of elapsed time.
    long  tv_nsec
    This is the rest of the elapsed time (a fraction of a second), represented as the number of nanoseconds.
*/

// Ojo hay que compilar g++ -Wall main.cpp -lrt para incluir las librerías de tiempos.


#include <cassert>
#include <ctime>
#include <cstdio>
#include <cstring> //Para usar memset
#include <iostream>
#include <stdint.h> // Para usar uint64_t

 /*!\brief Models a clock to measure performace.*/
  class Clock
  {
  private:
    timespec _start;
    timespec _stop;
    bool _isStarted;
  public:
    Clock ()
    {
      memset(&_start,0,sizeof(timespec));
      memset(&_stop,0,sizeof(timespec));
      _isStarted=false;
    }
    /*!\brief Starts the clock.
     * \pre not isStarted()
     * \post isStarted()
     */
    void start ()
    {
      assert (!isStarted());
      clock_gettime (CLOCK_REALTIME, &_start);
      _isStarted=true;
    }
    /*!\brief Re-starts the clock.
     * \post isStarted()
     */
    void restart ()
    {
      clock_gettime (CLOCK_REALTIME, &_start);
      _isStarted=true;
    }

    /*!\brief Stops the clock.
     * \pre isStarted()
     * \post not isStarted()
     */
    void stop ()
    {
      assert (_isStarted);
      clock_gettime (CLOCK_REALTIME, &_stop);
      _isStarted=false;
    }
    /*!\brief Is the clock started?
     * \return true if the clock is started currently.
     */
    bool isStarted() const
    {
      return _isStarted;
    }
    /*!\brief Return the elapsed time in mcs.*/
    uint64_t elapsed() const
    {
      assert (!_isStarted);
      uint64_t startT = (uint64_t)_start.tv_sec * 1000000LL + (uint64_t)_start.tv_nsec / 1000LL;
      uint64_t stopT = (uint64_t)_stop.tv_sec * 1000000LL + (uint64_t)_stop.tv_nsec / 1000LL;
      return stopT-startT;
    }
  };
