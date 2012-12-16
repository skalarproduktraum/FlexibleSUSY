
#ifndef SM_TWO_SCALE_H
#define SM_TWO_SCALE_H

#include "rge.h"
#include "two_scale_model.hpp"
#include "sm.hpp"

#include <iostream>

class Two_scale;

/// Formatted output
std::ostream& operator <<(std::ostream&, const StandardModel<Two_scale>&);

template<>
class StandardModel<Two_scale>: public Two_scale_model, protected RGE {
private:
   DoubleMatrix yu, yd, ye; ///< Yukawa matrices for ups, downs and leptons
   DoubleVector g;          ///< Gauge couplings (g1 = sqrt(5/3) g_Y)

public:
   const static int numStandardModelPars = 3 * 3 * 3 + 3;
   typedef enum {YU = 1, YD, YE} yukawa;

   StandardModel();
   StandardModel(const StandardModel<Two_scale>&);
   StandardModel(const DoubleMatrix& yu, const DoubleMatrix& yd,
                 const DoubleMatrix& ye, const DoubleVector& g);

   virtual ~StandardModel();

   virtual std::string name() const { return "SM"; }
   virtual int run_to(double scale, double eps = -1.0) { return RGE::runto(scale, eps); }
   virtual void print(std::ostream& s) const { s << *this; }

   /// sets object to be equal to another
   const StandardModel & operator=(const StandardModel<Two_scale>& s);

   /// Sets Yukawa matrix element
   void setYukawaElement(yukawa, int, int, double);
   /// Sets whole Yukawa matrix
   void setYukawaMatrix(yukawa, const DoubleMatrix&);
   /// Set a single gauge coupling
   virtual void setGaugeCoupling(int, double);
   /// Set all gauge couplings
   virtual void setAllGauge(const DoubleVector&);
   /// Sets renormalisation scale
   void setScale(double mu) { RGE::setMu(mu); }

   /// Returns a single Yukawa matrix element
   double displayYukawaElement(yukawa, int, int) const;
   /// Returns a whole Yukawa matrix
   DoubleMatrix displayYukawaMatrix(yukawa) const;
   /// Returns a single gauge coupling
   virtual double displayGaugeCoupling(int) const;
   /// Returns all gauge couplings
   virtual DoubleVector displayGauge() const;
   /// Return renomalisation scale
   double getScale() const { return RGE::displayMu(); }
   /// Return number of loops
   int displayLoops() const { return RGE::displayLoops(); }
   /// Return level of threshold approximation
   int displayThresholds() const { return RGE::displayThresholds(); }
   /// Calculate beta functions
   StandardModel calcBeta() const;

protected:
   /// Sets all RGE parameters to elements of vector
   virtual void set(const DoubleVector&);
   /// Returns all parameters as elements of a vector
   virtual const DoubleVector display() const;
   /// Calculate beta functions
   virtual DoubleVector beta() const;
};

#endif
