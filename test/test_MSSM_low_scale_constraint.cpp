
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_MSSM_low_scale_constraint

#include <boost/test/unit_test.hpp>
#include "test.h"
#include <functional>
#include <Eigen/Dense>

#define private public

#include "MSSM_model.hpp"
#include "MSSM_low_scale_constraint.hpp"
#include "softsusy.h"
#include "wrappers.hpp"
#include "ew_input.hpp"

void setup_MSSM(MSSM& m, MssmSoftsusy& s, const MSSM_input_parameters& input)
{
   const double ALPHASMZ = 0.1176;
   const double ALPHAMZ = 1.0 / 127.918;
   const double sinthWsq = 0.23122;
   const double alpha1 = 5 * ALPHAMZ / (3 * (1 - sinthWsq));
   const double alpha2 = ALPHAMZ / sinthWsq;
   const double g1 = sqrt(4 * Pi * alpha1);
   const double g2 = sqrt(4 * Pi * alpha2);
   const double g3 = sqrt(4 * Pi * ALPHASMZ);
   const double tanBeta = input.TanBeta;
   const double sinBeta = sin(atan(tanBeta));
   const double cosBeta = cos(atan(tanBeta));
   const double M12 = input.m12;
   const double m0 = input.m0;
   const double a0 = input.Azero;
   const double root2 = sqrt(2.0);
   const double vev = 246.0;
   const double vu = vev * sinBeta;
   const double vd = vev * cosBeta;
   const double susyMu = input.SignMu * 120.0;
   const double BMu = Sqr(2.0 * susyMu);
   const double scale = Electroweak_constants::MZ;

   DoubleMatrix Yu_SS(3,3), Yd_SS(3,3), Ye_SS(3,3);
   Yu_SS(3,3) = 165.0   * root2 / (vev * sinBeta);
   Yd_SS(3,3) = 2.9     * root2 / (vev * cosBeta);
   Ye_SS(3,3) = 1.77699 * root2 / (vev * cosBeta);
   DoubleMatrix ID(3, 3), mm0_SS(3, 3);
   for (int i=1; i<=3; i++) ID(i, i) = 1.0;
   mm0_SS = ID * sqr(m0);

   Eigen::Matrix<double,3,3> Yu(Eigen::Matrix<double,3,3>::Zero()),
      Yd(Eigen::Matrix<double,3,3>::Zero()),
      Ye(Eigen::Matrix<double,3,3>::Zero()),
      mm0(Eigen::Matrix<double,3,3>::Zero());
   Yu(2,2) = 165.0   * root2 / (vev * sinBeta);
   Yd(2,2) = 2.9     * root2 / (vev * cosBeta);
   Ye(2,2) = 1.77699 * root2 / (vev * cosBeta);
   mm0 = Sqr(m0) * Eigen::Matrix<double,3,3>::Identity();

   m.set_scale(scale);
   m.set_loops(1);
   m.set_g1(g1);
   m.set_g2(g2);
   m.set_g3(g3);
   m.set_Yu(Yu);
   m.set_Yd(Yd);
   m.set_Ye(Ye);
   m.set_MassB(M12);
   m.set_MassG(M12);
   m.set_MassWB(M12);
   m.set_mq2(mm0);
   m.set_ml2(mm0);
   m.set_md2(mm0);
   m.set_mu2(mm0);
   m.set_me2(mm0);
   m.set_mHd2(Sqr(m0));
   m.set_mHu2(Sqr(m0));
   m.set_TYu(a0 * Yu);
   m.set_TYd(a0 * Yd);
   m.set_TYe(a0 * Ye);
   m.set_Mu(susyMu);
   m.set_BMu(BMu);
   m.set_vu(vu);
   m.set_vd(vd);

   s.setMu(scale);
   s.setLoops(1);
   s.setGaugeCoupling(1, g1);
   s.setGaugeCoupling(2, g2);
   s.setGaugeCoupling(3, g3);
   s.setYukawaMatrix(YU, Yu_SS);
   s.setYukawaMatrix(YD, Yd_SS);
   s.setYukawaMatrix(YE, Ye_SS);
   s.setGauginoMass(1, M12);
   s.setGauginoMass(2, M12);
   s.setGauginoMass(3, M12);
   s.setSoftMassMatrix(mQl, mm0_SS);
   s.setSoftMassMatrix(mUr, mm0_SS);
   s.setSoftMassMatrix(mDr, mm0_SS);
   s.setSoftMassMatrix(mLl, mm0_SS);
   s.setSoftMassMatrix(mEr, mm0_SS);
   s.setMh1Squared(sqr(m0));
   s.setMh2Squared(sqr(m0));
   s.setTrilinearMatrix(UA, a0 * Yu_SS);
   s.setTrilinearMatrix(DA, a0 * Yd_SS);
   s.setTrilinearMatrix(EA, a0 * Ye_SS);
   s.setSusyMu(susyMu);
   s.setM3Squared(BMu);
   s.setHvev(vev);
   s.setTanb(tanBeta);
}

DoubleVector calculate_gauge_couplings(MSSM model, MSSM_low_scale_constraint constraint, double scale)
{
   model.set_scale(scale);
   constraint.set_model(&model);
   constraint.calculate_DRbar_gauge_couplings();

   DoubleVector g(3);
   g(1) = model.get_g1();
   g(2) = model.get_g2();
   g(3) = model.get_g3();

   return g;
}

BOOST_AUTO_TEST_CASE( test_threshold_corrections )
{
   MSSM m; MssmSoftsusy s;
   MSSM_input_parameters input;
   setup_MSSM(m, s, input);
   m.solve_ewsb(0);
   m.calculate_DRbar_parameters();

   MSSM_low_scale_constraint constraint(input);

   const double Q1 = constraint.get_scale();
   const double Q2 = 2. * Q1;
   const double gut_normalization = 3./5.;
   DoubleVector g_old(3);
   g_old(1) = m.get_g1();
   g_old(2) = m.get_g2();
   g_old(3) = m.get_g3();
   DoubleVector prefactor(3);
   for (int i = 1; i <= 3; i++)
      prefactor(i) = 1. / (oneOver16PiSqr * Power(g_old(i),3));

   const DoubleVector g_Q1(calculate_gauge_couplings(m, constraint, Q1));
   const DoubleVector g_Q2(calculate_gauge_couplings(m, constraint, Q2));

   const DoubleVector beta_numeric((g_Q1 - g_Q2) * prefactor * (1. / log(Q1/Q2)));
   DoubleVector beta_SM(3);
   beta_SM(1) = 41./6. * gut_normalization;
   beta_SM(2) = -19./6.;
   beta_SM(3) = -7.;
   DoubleVector beta_MSSM(3);
   beta_MSSM(1) = 11. * gut_normalization;
   beta_MSSM(2) = 1.;
   beta_MSSM(3) = -3.;

   BOOST_CHECK_CLOSE_FRACTION(beta_numeric(1), beta_MSSM(1) - beta_SM(1), 0.2);
   BOOST_CHECK_CLOSE_FRACTION(beta_numeric(2), beta_MSSM(2) - beta_SM(2), 0.21);
   BOOST_CHECK_CLOSE_FRACTION(beta_numeric(3), beta_MSSM(3) - beta_SM(3), 0.011);
}

BOOST_AUTO_TEST_CASE( test_low_energy_constraint )
{
   MSSM_input_parameters input;
   MSSM m; MssmSoftsusy s;
   setup_MSSM(m, s, input);
   m.solve_ewsb(0);
   m.calculate_DRbar_parameters();
   s.calcDrBarPars();

   MSSM_low_scale_constraint constraint(input);
   constraint.set_model(&m);

   // apply constraints
   constraint.apply();
   s.sparticleThresholdCorrections(input.TanBeta);

   // BOOST_CHECK_CLOSE_FRACTION(m.get_g1(), s.displayGaugeCoupling(1), 0.002);
   // BOOST_CHECK_CLOSE_FRACTION(m.get_g2(), s.displayGaugeCoupling(2), 0.002);
   BOOST_CHECK_CLOSE_FRACTION(m.get_g3(), s.displayGaugeCoupling(3), 0.002);

   // test off-diagonal elements
   BOOST_MESSAGE("testing off-diagonal yukawa elements");
   for (int i = 1; i <= 3; i++) {
      for (int k = 1; k <= 3; k++) {
         if (i == k)
            continue;
         BOOST_MESSAGE("testing yukawa elements " << i << ", " << k);
         BOOST_CHECK_CLOSE_FRACTION(m.get_Yu()(i-1,k-1), s.displayYukawaMatrix(YU)(i,k), 0.00001);
         BOOST_CHECK_CLOSE_FRACTION(m.get_Yd()(i-1,k-1), s.displayYukawaMatrix(YD)(i,k), 0.00001);
         BOOST_CHECK_CLOSE_FRACTION(m.get_Ye()(i-1,k-1), s.displayYukawaMatrix(YE)(i,k), 0.00001);
      }
   }

   BOOST_MESSAGE("testing diagonal yukawa elements");
   BOOST_CHECK_CLOSE_FRACTION(m.get_Yu()(0,0), s.displayYukawaMatrix(YU)(1,1), 0.3);
   BOOST_CHECK_CLOSE_FRACTION(m.get_Yd()(0,0), s.displayYukawaMatrix(YD)(1,1), 0.25);
   BOOST_CHECK_CLOSE_FRACTION(m.get_Ye()(0,0), s.displayYukawaMatrix(YE)(1,1), 0.025);

   BOOST_CHECK_CLOSE_FRACTION(m.get_Yu()(1,1), s.displayYukawaMatrix(YU)(2,2), 0.15);
   BOOST_CHECK_CLOSE_FRACTION(m.get_Yd()(1,1), s.displayYukawaMatrix(YD)(2,2), 0.17);
   BOOST_CHECK_CLOSE_FRACTION(m.get_Ye()(1,1), s.displayYukawaMatrix(YE)(2,2), 0.02);

   BOOST_CHECK_CLOSE_FRACTION(m.get_Yu()(2,2), s.displayYukawaMatrix(YU)(3,3), 0.013);
   BOOST_CHECK_CLOSE_FRACTION(m.get_Yd()(2,2), s.displayYukawaMatrix(YD)(3,3), 0.095);
   BOOST_CHECK_CLOSE_FRACTION(m.get_Ye()(2,2), s.displayYukawaMatrix(YE)(3,3), 0.025);
}