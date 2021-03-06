
/** \file softpoint.cpp
    - Project:     SOFTSUSY 
   - Authors:     Ben Allanach, Markus Bernhardt 
   - Manual:      hep-ph/0104145, Comp. Phys. Comm. 143 (2002) 305 

   - Webpage:     http://hepforge.cedar.ac.uk/softsusy/
   - Description: main calling program: command line interface. Reads Les
   - Houches files and command-line inputs and drives the calculation of a point
   - in parameter space.
*/ 

#include "run_softpoint.h"

// Returns a string with all characters in upper case: very handy
string ToUpper(const string & s) {
        string result;
        unsigned int index;
        for (index = 0; index < s.length(); index++) {
	  char a = s[index];
	  a = toupper(a);
	  result = result + a;
        }
	
	return result;
    }

void errorCall() {
  ostringstream ii;
  ii << "SOFTSUSY" << SOFTSUSY_VERSION 
     << " called with incorrect arguments. Need to put either:\n";
  ii << "softpoint.x leshouches < lesHouchesInput\n for SLHA input, or\n";
  ii << "softpoint.x sugra <m0> <m12> <a0> <tanb> <mgut> <sgnMu>\n";
  ii << "softpoint.x amsb <m0> <m32> <tanb> <mgut> <sgnMu>\n";
  ii << "softpoint.x gmsb <n5> <mMess> <lambda> <cgrav> <tanb> <sgnMu> \n";
  ii << "Any of the above can be extended by R-parity violation of one coupling by\n";
  ii << "softpoint.x <non RPV model parameters as above> lambda <i> <j> <k> <coupling> \n";
  ii << "the word lambda replaceable with lambdaP or lambdaPP for LLE, LQD, UDD coupling, respectively \n\n";
  ii << "Other possibilities:\n";
  ii << "softpoint.x sugra <m0> <m12> <a0> <tanb> <mgut> <sgnMu> <mb(mb)> ";
  ii << " <mt> <as(MZ)> <1/a(MZ)>\n";
  ii << "Bracketed entries are numerical values.\n";
  ii << "<mgut> denotes the scale at which the SUSY breaking ";
  ii << "parameters are specified. \n";
  ii << "Enter <mgut>=unified to define MGUT by g1(MGUT)=g2(MGUT), otherwise";
  ii << "\nit will be fixed at the numerical value input.\n";
  ii << "For SUSY breaking terms set at MSUSY, enter <mgut>=msusy.\n";
  ii << "lesHouchesInput contains the SUSY Les Houches Accord 2";
  ii << " input.\n";
  ii << "\n"
     "NMSSM command line options:\n"
     "  softpoint.x nmssm <gut-condition> [flags] [parameters]\n"
     "\n"
     "Gut conditions: sugra\n"
     "\n"
     "Flags:\n"
     "  --lambdaAtMsusy   input lambda at renormalization scale Q = Msusy\n"
     "\n"
     "Parameters:\n"
     "  --m0= , --m12= , --a0= , --tanBeta= , --mHd2= , --mHu2= ,\n"
     "  --mu= , --BmuOverCosBetaSinBeta= , --lambda= , --kappa= ,\n"
     "  --Alambda= , --Akappa= , --lambdaS= , --xiF= , --xiS= ,\n"
     "  --muPrime= , --mPrimeS2= , --mS2=\n"
     "\n"
     "  Note: unset parameters are assumed to be zero\n"
     "\n"
     "Example:\n"
     "  softpoint.x nmssm sugra --m0=125 --m12=200 --tanBeta=10 --a0=-300 \\\n"
     "     --lambda=0.1 --lambdaAtMsusy\n";
  throw ii.str();
}

int main(int argc, char *argv[]) {
  tryToConvergeHard = true;
  /// Sets up exception handling
  signal(SIGFPE, FPE_ExceptionHandler); 

  double lambda = 0., aCkm = 0., rhobar = 0., etabar = 0.;
  NMSSM_input nmssm_input; // NMSSM input parameters

  bool flavourViolation = false;

  int numPoints = 1;

  double qMax = 0.;

  // Sets format of output: 4 decimal places
  outputCharacteristics(6);

  void (*boundaryCondition)(MssmSoftsusy &, const DoubleVector &)=sugraBcs;
  void (*nmssmBoundaryCondition)(NmssmSoftsusy&, const DoubleVector&) = NmssmMsugraBcs;

  QedQcd oneset;
  MssmSoftsusy m;
  NmssmSoftsusy nmssm;
  MssmSoftsusy * r = &m; 
  bool RPVflag = false;
  enum Model_t { MSSM, NMSSM } susy_model = MSSM; // susy model (MODSEL entry 3)
  softsusy::GUTlambda = true;
  bool oldSchoolRpvOutput = false;

  try {
  if (argc !=1 && strcmp(argv[1],"leshouches") != 0) {
    cerr << "SOFTSUSY" << SOFTSUSY_VERSION << endl;
    cerr << "B.C. Allanach, Comput. Phys. Commun. 143 (2002) 305-331,";
    cerr << " hep-ph/0104145\n";
    cerr << "For RPV aspects, B.C. Allanach and M.A. Bernhardt, ";
    cerr << "arXiv:0903.1805.\n\n";
    cerr << "Low energy data in SOFTSUSY: MIXING=" << MIXING << " TOLERANCE=" 
	 << TOLERANCE << endl;
    cerr << "G_F=" << GMU << " GeV^2" << endl;
  }
  
  double mgutGuess = 2.0e16, tanb = 10.;
  int sgnMu = 1;
  bool gaugeUnification = true, ewsbBCscale = false;
  double desiredMh = 0.;

    // If there are no arguments, give error message,
   // or if none of the options are called, then go to error message
    if (argc == 1 || (strcmp(argv[1], "sugra") && strcmp(argv[1], "amsb") &&
		      strcmp(argv[1], "gmsb") && 
		      strcmp(argv[1], "runto") && strcmp(argv[1], "nmssm") &&
		      strcmp(argv[1], "leshouches")  && strcmp(argv[1], "-v") &&
		      strcmp(argv[1], "--version")))
      errorCall();
    
    DoubleVector pars(3); 
    
    std::string modelIdent;

    if (!strcmp(argv[1], "sugra")) {
      cout << "# SOFTSUSY SUGRA calculation" << endl;
      boundaryCondition = &sugraBcs;
      if (argc == 8) {
	modelIdent = "sugra";
	double m0 = atof(argv[2]);
	double m12 = atof(argv[3]);
	double a0 = atof(argv[4]);
	tanb = atof(argv[5]);
	mgutGuess = mgutCheck(argv[6], gaugeUnification, ewsbBCscale);
	sgnMu =  atoi(argv[7]);
	pars(1) = m0; pars(2) = m12; pars(3) = a0;
	r = &m;
      } else if (argc == 9) {
	modelIdent = "sugra";
	double m0 = atof(argv[2]);
	double m12 = atof(argv[3]);
	double a0 = atof(argv[4]);
	tanb = atof(argv[5]);
	mgutGuess = mgutCheck(argv[6], gaugeUnification, ewsbBCscale);
	sgnMu =  atoi(argv[7]);
	pars(1) = m0; pars(2) = m12; pars(3) = a0;
	QEWSB = atof(argv[8]);
	r = &m;
      } else if (argc == 12) {
	modelIdent = "sugra";
	double m0 = atof(argv[2]);
	double m12 = atof(argv[3]);
	double a0 = atof(argv[4]);
	tanb = atof(argv[5]);
	mgutGuess = mgutCheck(argv[6], gaugeUnification, ewsbBCscale);
	sgnMu =  atoi(argv[7]);
	double mbrun = atof(argv[8]);
	double mtpole = atof(argv[9]);
	double as = atof(argv[10]);
	double aInv = atof(argv[11]);
	oneset.setMass(mBottom, mbrun);
	oneset.setMbMb(mbrun);
	oneset.setPoleMt(mtpole);
	oneset.setAlpha(ALPHA, 1.0 / aInv);
	oneset.setAlpha(ALPHAS, as);
	pars(1) = m0; pars(2) = m12; pars(3) = a0;
	r = &m;
      } else if (argc == 13) {
	RPVflag = true;
	modelIdent = "sugra";
	double m0 = atof(argv[2]);
	double m12 = atof(argv[3]);
	double a0 = atof(argv[4]);
	tanb = atof(argv[5]);
	mgutGuess = mgutCheck(argv[6], gaugeUnification, ewsbBCscale);
	sgnMu =  atoi(argv[7]);
	pars(1) = m0; pars(2) = m12; pars(3) = a0;
	// check which lambda is set nonzero at MGUT
	if (!strcmp(argv[8], "lambda")) {
	  int i= int(atof(argv[9]));
	  int j= int(atof(argv[10]));
	  int k= int(atof(argv[11]));
	  double d = atof(argv[12]);
	} else if (!strcmp(argv[8], "lambdaP")) {
	  modelIdent = "sugra";
	  int i= int(atof(argv[9]));
	  int j= int(atof(argv[10]));
	  int k= int(atof(argv[11]));
	  double d = atof(argv[12]);
	} else if (!strcmp(argv[8], "lambdaPP")) {
	  modelIdent = "sugra";
	  int i= int(atof(argv[9]));
	  int j= int(atof(argv[10]));
	  int k= int(atof(argv[11]));
	  double d = atof(argv[12]);
	}
	r = &m;
      } else if (argc == 11) {
	modelIdent = "sugra";
	RPVflag = true;
	double m0 = atof(argv[2]);
	double m12 = atof(argv[3]);
	double a0 = atof(argv[4]);
	tanb = atof(argv[5]);
	mgutGuess = mgutCheck(argv[6], gaugeUnification, ewsbBCscale);
	sgnMu =  atoi(argv[7]);
	pars(1) = m0; pars(2) = m12; pars(3) = a0;
	// check which lambda is set nonzero at MGUT
	if (!strcmp(argv[8], "kappa")) {
	  int i = int(atof(argv[9]));
	  double d = atof(argv[10]);
	}
	r = &m;
      } 
      else {
	errorCall();
	// end of SUGRA option
      }
    }
    if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")) return 0;
    if (!strcmp(argv[1], "amsb")) {
      cout << "# SOFTSUSY mAMSB calculation" << endl;
      boundaryCondition = &amsbBcs;
      if (argc == 7 || argc == 12) {
	modelIdent = "amsb";
	double m0 = atof(argv[2]);
	double m32 = atof(argv[3]);
	tanb = atof(argv[4]);
	mgutGuess = mgutCheck(argv[5], gaugeUnification, ewsbBCscale);
	sgnMu =  atoi(argv[6]);
	pars(1) = m32; pars(2) = m0;
	// check if RPV
	if (argc == 12) {
	  if (!strcmp(argv[7], "lambda")) {
	    RPVflag = true;
	    int i= int(atof(argv[8]));
	    int j= int(atof(argv[9]));
	    int k= int(atof(argv[10]));
	    double d = atof(argv[11]);
	  }	
	  else if (!strcmp(argv[7], "lambdaP")) {
	    RPVflag = true;
	    int i= int(atof(argv[8]));
	    int j= int(atof(argv[9]));
	    int k= int(atof(argv[10]));
	    double d = atof(argv[11]);
	  } else if (!strcmp(argv[7], "lambdaPP")) {
	    RPVflag = true;
	    int i= int(atof(argv[8]));
	    int j= int(atof(argv[9]));
	    int k= int(atof(argv[10]));
	    double d = atof(argv[11]);
	  }
	}
	r = &m;
      }
      else 
	errorCall();
    }
    if (!strcmp(argv[1], "gmsb")) {
      cout << "# SOFTSUSY mGMSB calculation" << endl;
      
      boundaryCondition = &gmsbBcs;
      modelIdent = "gmsb";
      if (argc == 8) {
	  double n5 = atof(argv[2]);
	  double mMess = atof(argv[3]);
	  double lambda = atof(argv[4]);
	  double cgrav = atof(argv[5]);
	  tanb = atof(argv[6]);
	  sgnMu =  atoi(argv[7]);
	  mgutGuess = mMess;
	  gaugeUnification = false;
	  pars.setEnd(4);
	  pars(1) = n5; pars(2) = mMess; pars(3) = lambda; pars(4) = cgrav;
	  r = &m;
	  if (lambda > mMess) {
	  ostringstream ii;
	  ii << "Input lambda=" << lambda << " should be less than mMess="
	     << mMess << endl;
	  throw ii.str();
	}
	if (cgrav > 1.0) {
	  ostringstream ii;
	  ii << "Input cgrav=" << cgrav << " a real number bigger than or "
	     << " equal to 1 (you can use 1 as a default value).\n";
	  throw ii.str();
	}
      }
      // for RPV GMSB
      else if (argc == 13) {
	modelIdent = "gmsb";
	RPVflag = true;
	double n5 = atof(argv[2]);
	double mMess = atof(argv[3]);
	double lambda = atof(argv[4]);
	double cgrav = atof(argv[5]);
	tanb = atof(argv[6]);
	sgnMu =  atoi(argv[7]);
	mgutGuess = mMess;
	gaugeUnification = false;
	pars.setEnd(4);
	pars(1) = n5; pars(2) = mMess; pars(3) = lambda; pars(4) = cgrav;
	// check which lambda is set nonzero at MGUT
	if (!strcmp(argv[8], "lambda")) {
	  int i= int(atof(argv[9]));
	  int j= int(atof(argv[10]));
	  int k= int(atof(argv[11]));
	  double d = atof(argv[12]);
	} else if (!strcmp(argv[8], "lambdaP")) {
	  int i= int(atof(argv[9]));
	  int j= int(atof(argv[10]));
	  int k= int(atof(argv[11]));
	  double d = atof(argv[12]);
	} else if (!strcmp(argv[8], "lambdaPP")) {
	  int i= int(atof(argv[9]));
	  int j= int(atof(argv[10]));
	  int k= int(atof(argv[11]));
	  double d = atof(argv[12]);
	}
	r = &m;
	if (lambda < mMess) {
	  ostringstream ii;
	  ii << "Input lambda=" << lambda << " should be greater than mMess="
	     << mMess << endl;
	  throw ii.str();
	}
	if (cgrav > 1.0) {
	  ostringstream ii;
	  ii << "Input cgrav=" << cgrav << " a real number bigger than or "
	     << " equal to 1 (you can use 1 as a default value).\n";
	  throw ii.str();
	}
      }
      else 
	errorCall();
    }
    if (!strcmp(argv[1], "nmssm")) {
      susy_model = NMSSM;
      NMSSM_command_line_parser nmssm_parser(&nmssm_input);
      nmssm_parser.parse(argc, argv);
      modelIdent = nmssm_parser.get_modelIdent();
      pars = nmssm_parser.get_pars();
      cout << "# SOFTSUSY NMSSM " << modelIdent << " calculation\n";
    }
    
    bool flag = false;
    if (!strcmp(argv[1], "leshouches")) {
      outputCharacteristics(8);
      if (argc == 2) {
	string line, block;
	int model;
	
	while (getline(cin,line)) {
	  //	  mgutGuess = mgutCheck("unified", gaugeUnification);

	  //	cout << line << endl;
	  istringstream input(line); 
	  string word1, word2;
	  input >> word1;
	  
	  if (word1.find("#") == string::npos) { 
	    // read in another word if there's no comment
	    input >> word2; 
	    
	    if (ToUpper(word1) == "BLOCK")  { 
	      block = ToUpper(word2);
	      
	    } else { // ought to be data
	      istringstream kk(line);
	      if (block == "MODSEL") {
		int i; kk >> i; 
		
		switch(i) {
		case 1: kk >> model; 
		  switch(model) {
		  case 0: boundaryCondition = &extendedSugraBcs;
		    modelIdent = "nonUniversal"; r=&m;
		    break;
		  case 1: 
		    if (!flavourViolation) {
		      pars.setEnd(3); 
		      boundaryCondition = &sugraBcs; 
		    }
		    modelIdent = "sugra";
		    break;
		  case 2: 
		    if (!flavourViolation) {
		      boundaryCondition = &gmsbBcs; 
		      pars.setEnd(4); 
		    } 
		    modelIdent = "gmsb";
		    break;
		  case 3: 		    
		    boundaryCondition = &amsbBcs; 
		    pars.setEnd(2); 
		    modelIdent = "amsb";
		    break;
		  case 4:
		    pars.setEnd(7); sgnMu = 0; 
		    modelIdent = "splitgmsb";
		    break;
		  default: 
		    ostringstream ii;
		    ii << "SOFTSUSY" << SOFTSUSY_VERSION 
		       << " cannot yet do model " 
		       << model << ": terminal error\n";
		    throw ii.str();
		  }
		  break;
                // reading entry 3: susy model (MSSM, NMSSM, ...)
                case 3: { int i; kk >> i;
		  switch(i) {
		  case 0: susy_model = MSSM; // default
		    break;
		  case 1: susy_model = NMSSM;
                     if (flavourViolation) {
                        flavourViolation = false;
                        cout << "# Warning: flavour violation is currtently"
                           " not supported in the NMSSM\n";
                     }
		    break;
		  default:
		    ostringstream ii;
		    ii << "MODSEL 3 choosing silly model switch\n"
		       << "(" << i << ") not a valid switch" << endl;
		    throw ii.str();
                  }
                  }
		  break;
		case 4: int i; kk >> i;
		  switch(i) {
		  case 0: RPVflag = false;
		    break;
		  case 1: RPVflag = true;
		    break;
		  default:
		    ostringstream ii;
		    ii << "MODSEL 4 choosing silly RPV switch\n"
		       << "(" << i << ") not a valid switch" << endl;
		    throw ii.str();
		  }
		  break;
		case 6: int j; kk >> j;
		  switch(j) {
		  case 0: flavourViolation = false; break;
		  default:
                     if (susy_model == NMSSM) {
                        flavourViolation = false;
                        cout << "# Warning: flavour violation is currtently"
                           " not supported in the NMSSM\n";
                     } else {
                        flavourViolation = true;
                        if (boundaryCondition != & amsbBcs) {
                           pars.setEnd(64);
                        }
                     }
		  }
		  break;
		case 11: kk >> numPoints;
		  if (numPoints < 1) {
		    ostringstream ii;
		    ii << "MODSEL 11 selecting silly number of points"
		       << "(" << numPoints << ") to output" << endl;
		    throw ii.str();
		  }
		  break;
		case 12: double d; kk >> d;
		  if (d < MZ) {
		    ostringstream ii;
		    ii << "MODSEL 12 selecting silly scale Qmax"
		       << "(" << d << ") < MZ to output" << endl;
		    throw ii.str();
		  }
		  qMax = d; break;
		default:
		  cout << "# WARNING: don't understand first integer " 
		       << word1 << " " << word2 << " in block " << block
		       << ": ignoring it\n";
		  break;
		}
	      }
	      else if (block == "MINPAR") {
		int i; double d; kk >> i >> d; 
		switch (i) {
		case 3: tanb = d;
                   nmssm_input.set(NMSSM_input::tanBeta, d);
                   break;
		case 4: sgnMu = int(d); break;
		default: 
		  switch(model) {
		  case 0:
		    // SUGRA inputs to fill out the pheno MSSM case
		    switch(i) {
		    case 1: pars(1) = d; break;
		    case 2: pars(2) = d; break;
		    case 5: pars(3) = d; break;
		    default: 
		      ostringstream ii;
		      ii << "Didn't understand pheno MSSM input " << i << endl;
		      break;
		    } break;
		  case 1: // SUGRA inputs
		    switch(i) {
		    case 1: 
		      if (flavourViolation) { pars.setEnd(77);
			double m0 = sqr(d);
			pars(4) = m0; pars(7) = m0; pars(9) = m0;
			pars(10) = m0; pars(13) = m0; pars(15) = m0; 
			pars(16) = m0; pars(19) = m0; pars(21) = m0; 
			pars(22) = m0; pars(25) = m0; pars(27) = m0; 
			pars(28) = m0; pars(31) = m0; pars(33) = m0; 
			pars(63) = m0; pars(64) = m0;
		      } else pars(1) = d; 
		      break;
		    case 2: 
		      if (flavourViolation) {
			pars(1) = d; pars(2) = d; pars(3) = d;
		      } else pars(2) = d; 
		      break;
		    case 5: 
		      if (flavourViolation) {
			pars.setEnd(77);
			pars(62) = d;

		      } else pars(3) = d; 
		      break;
		    default: 
		      ostringstream ii;
		      ii << "Didn't understand SUGRA input " << i << endl;
		      break;
		    } break;
		  case 2: // GMSB inputs
		    switch(i) {
		    case 1: pars(3) = d; break;
		    case 2: pars(2) = d; mgutGuess = d;
		      gaugeUnification = false; break;
		    case 5: pars(1) = d; break;
		    case 6: pars(4) = d; break;
		    default: 
		      ostringstream ii;
			ii << "Didn't understand GMSB input " << i << endl;
			break;
		    } break;
		  case 3: ///< AMSB inputs
		    switch(i) {
		    case 1: pars(2) = d; break;
		    case 2: pars(1) = d; break;
		    default: 
		      ostringstream ii;
		      ii << "Didn't understand AMSB input " << i << endl;
		      break;
		    } break;
		  case 4: ///< split GMSB inputs 
		    switch(i) {
		    case 1: pars(2) = d; break;
		    case 2: pars(3) = d; break;
		    case 5: pars(1) = d; break;
		    case 6: pars(7) = d; break;
		    case 7: pars(4) = d; mgutGuess = d; 
		      gaugeUnification = false; break;
		    case 8: pars(5) = d; break;
		    case 9: pars(6) = d; m.useAlternativeEwsb(); 
		      break;
		    case 10: desiredMh = d; break;
		    default: 
		      ostringstream ii;
			ii << "Didn't understand GMSB input " << i << endl;
			break;
		    } break;
		  default: 
		    ostringstream ii;
		    ii << "Didn't understand model input " << model << endl;
		    break;
		  }
		  break;
		}
	      }
	      // Adding non-minimal options. 
	      else if (block == "EXTPAR") {
                int i; double d; kk >> i >> d;

                // read extra NMSSM input parameters from EXTPAR
                // (skipping NMSSM parameters if the MSSM was selected)
                if (susy_model == MSSM) {
                   switch (i) {
                   case 61:
                   case 62:
                   case 63:
                   case 64:
                   case 65:
                   case 66:
                   case 67:
                   case 68:
                   case 69:
                   case 70:
                      cout << "# Warning: NMSSM parameter EXTPAR " << i
                           << " given but MSSM chosen -- ignoring it.\n";
                      continue;
                   }
                } else if (susy_model == NMSSM) {
                   // read NMSSM susy parameters only and continue
                   switch (i) {
                   case 61: nmssm_input.set(NMSSM_input::lambda , d); continue;
                   case 62: nmssm_input.set(NMSSM_input::kappa  , d); continue;
                   case 65: nmssm_input.set(NMSSM_input::lambdaS, d); continue;
                   case 66: nmssm_input.set(NMSSM_input::xiF    , d); continue;
                   case 68: nmssm_input.set(NMSSM_input::muPrime, d); continue;
                   }
                }

		/// First, we want to convert our input to EXTPAR if we have
		/// mSUGRA already
		if (modelIdent == "sugra") {
		  modelIdent = "nonUniversal";
		  if (!flavourViolation) {
		    /// We assume mSUGRA BCs with no flavour violation
		    r=&m; 
		    boundaryCondition = &extendedSugraBcs;
		    double m0 = pars(1), m12 = pars(2), a0 = pars(3);
		    pars.setEnd(49);
		    int i; for (i=1; i<=3; i++) pars(i) = m12;
		    for (i=11; i<=13; i++) pars(i) = a0;
		    pars(21) = m0*m0; pars(22) = m0*m0;
		    for (i=31; i<=36; i++) pars(i) = m0;		    
		    for (i=41; i<=49; i++) pars(i) = m0;		    
                    if (susy_model == NMSSM) {
                       pars.setEnd(53);
                       pars(50) = a0; // Alambda
                       pars(51) = a0; // Akappa
                       pars(52) = 0.; // mS'^2 @todo which value should we chose here?
                       pars(53) = m0*m0; // mS^2
                    }
		  } else {
		    /// This is flavour violation with EXTPAR: mSUGRA BCs
		    /// with flavour violation
		    if (pars.displayEnd() == 3) {
		      double m0 = pars(1), m12 = pars(2), a0 = pars(3);
		      double msq = m0 * m0;
		      pars.setEnd(77);
		      int i; for (i=1; i<=3; i++) pars(i) = m12;
		      /// Fill in scalar mass squareds
		      for (i=1; i<=5; i++) {
			int num = (i-1) * 6 + 4;
			pars(num)  = msq; 
			pars(num+3)  = msq; 
			pars(num+5)  = msq;
		      }
		    
		    pars(62) = a0;
		    pars(63) = msq; pars(64) = msq;
		    }
		  }
		}
		
		if (modelIdent == "nonUniversal") {
		  /// First, put parameters that depend not on
		  /// flavoured/unflavoured input
		  if (i == 0) { 
		    mgutGuess = d;
		    gaugeUnification = false;
		    // setting Minput=-1 should yield MSSM BCs at MSUSY
		    if (fabs(d + 1.0) < EPSTOL) {
		      mgutGuess = 1.0e3;
		      ewsbBCscale = true;
		      QEWSB = 1.0;
		      if (gaugeUnification) 
			cout << "# Gauge unification ignored since pheno MSSM"
			     << " assumes BC set at QEWSB\n"; 
		      gaugeUnification = false;
		    }
		  }
		  else if (i == 25) {
		    tanb = d;
		    if (pars.displayEnd() != 49) pars.setEnd(49);
		    pars(i) = d;
		    r->setSetTbAtMX(true);
		  } 
		  else if (i == 23 || i == 26) {
		    r->useAlternativeEwsb(); 
		    if (i == 23) {
                       r->setMuCond(d); r->setSusyMu(d);
                       nmssm_input.set(NMSSM_input::mu, d);
                    }
		    if (i == 26) r->setMaCond(d); 
		  }
		  else if (!flavourViolation) {
		    if ((i > 0 && i <=  3) || (i >= 11 && i <= 13) || 
			(i >= 21 && i <= 23) || (i == 26 || i == 25) 
			|| (i >= 31 && i <= 36) || 
			(i >= 41 && i <= 49)) {
		      if (pars.displayEnd() < 49) pars.setEnd(49);
		      pars(i) = d;
                      if (susy_model == NMSSM) {
                         if (pars.displayEnd() < 53) pars.setEnd(53);
                         switch (i) {
                         case 21: nmssm_input.set(NMSSM_input::mHd2, d); break;
                         case 22: nmssm_input.set(NMSSM_input::mHu2, d); break;
                         case 23: nmssm_input.set(NMSSM_input::mu  , d); break;
                         }
                      }
		    } else if ((61 <= i && i <= 70) || i == 24) {
                       switch (i) {
                       case 24:
                          nmssm_input.set(NMSSM_input::BmuOverCosBetaSinBeta, d);
                          break;
                       case 63:
                          nmssm_input.set(NMSSM_input::Alambda, d);
                          pars(50) = d;
                          break;
                       case 64:
                          nmssm_input.set(NMSSM_input::Akappa, d);
                          pars(51) = d;
                          break;
                       case 67:
                          nmssm_input.set(NMSSM_input::xiS, d);
                          // @todo currently not set in extendedNMSugraBcs()
                          break;
                       case 69:
                          nmssm_input.set(NMSSM_input::mPrimeS2, d);
                          pars(52) = d;
                          break;
                       case 70:
                          nmssm_input.set(NMSSM_input::mS2, d);
                          pars(53) = d;
                          break;
                       }
		    } else {
		      cout << "WARNING: did not understand parameter " 
			   << i << " in non-flavoured EXTPAR inputs\n";
		    }
		  } else {
		    /// Have to translate the numbers from SLHA to your
		    /// convention with flavour violation
		    if ((i > 0 && i < 4)) pars(i) = d; 
		    else if (i == 31) pars(22) = sqr(d);
		    else if (i == 32) pars(25) = sqr(d);
		    else if (i == 33) pars(27) = sqr(d);
		    else if (i == 34) pars(28) = sqr(d);
		    else if (i == 35) pars(31) = sqr(d);
		    else if (i == 36) pars(33) = sqr(d);
		    else if (i == 41) pars(4) = sqr(d);
		    else if (i == 42) pars(7) = sqr(d);
		    else if (i == 43) pars(9) = sqr(d);
		    else if (i == 44) pars(10) = sqr(d);
		    else if (i == 45) pars(13) = sqr(d);
		    else if (i == 46) pars(15) = sqr(d);
		    else if (i == 47) pars(16) = sqr(d);
		    else if (i == 48) pars(19) = sqr(d);
		    else if (i == 49) pars(21) = sqr(d);
		    else if (i == 21) pars(63) = d;
		    else if (i == 22) pars(64) = d;
		    else if (i > 10 && i < 14) 
		      cout << "WARNING: At,Ab,Atau are for SLHA1 only. "
			   << "Setting them to zero.\n"
			   << "Please use blocks TUIN, TDIN, TEIN for "
			   << "flavour violating SLHA input\n";
		    else {
		      cout << "WARNING: did not understand parameter " 
			   << i << " in flavoured EXTPAR inputs\n";
		    }
		  }
		}
	      }
              else if (block == "QEXTPAR") {
                int i; double d; kk >> i >> d;
                if (susy_model == NMSSM) {
                   switch (i) {
                   case 61: // scale where to input lambda
                      if (fabs(d + 1.0) < EPSTOL) {
                         softsusy::GUTlambda = false;
                      } else {
                         cout << "WARNING: cannot input NMSSM parameter lambda"
                            " (set in QEXTPAR " << i << ") at a scale "
                            "different from M_susy.  Please set QEXTPAR "
                              << i << " to -1 (M_susy) or remove the entry.\n";
                      }
                      break;
                   default:
                      cout << "WARNING: cannot use parameter " << i <<
                         " (set in QEXTPAR) as input at a different"
                         " scale (in the NMSSM) -- ignoring the scale choice\n";
                   }
                   continue;
                }
                cout << "WARNING: cannot use parameter " << i <<
                   " (set in QEXTPAR) as input at a different"
                   " scale -- ignoring the scale choice\n";
              }
	      else if (block == "VCKMIN") {
		int i; double d; kk >> i >> d;
		switch(i) {
		case 1: lambda = d; break;
		case 2: aCkm = d;   break;		  
		case 3: rhobar = d; break;
		case 4: etabar = d; break;
		default:
		  cout << "# WARNING: Don't understand data input " << i 
		       << " " << d << " in block "
		       << block << ": ignoring it\n";
		  break;
		}
	      }
	      else if (block == "UMNSIN") {
		int i; double d; kk >> i >> d;
		switch(i) {
		case 1: break;
		case 2: break;		  
		case 3: break;
		case 4: cout << "# Cannot yet do complex phases: ";
		  cout << "setting it to zero" << endl; break;
		case 5: cout << "# Cannot yet do complex phases: ";
		  cout << "setting it to zero" << endl; break;
		case 6: cout << "# Cannot yet do complex phases: ";
		  cout << "setting it to zero" << endl; break;
		default:
		  cout << "# WARNING: Don't understand data input " << i 
		       << " " << d << " in block "
		       << block << ": ignoring it\n";
		  break;
		}
	      }
	      else if (block == "SMINPUTS") {
		int i; double d; kk >> i >> d; 
		switch (i) {
		case 1: oneset.setAlpha(ALPHA, 1.0 / d); break;
		case 2: GMU = d; break;
		case 3: oneset.setAlpha(ALPHAS, d); break; 
		case 4: oneset.setMu(d); m.setData(oneset); MZ = d; break;
		case 5: oneset.setMass(mBottom, d); flag = true; 
		  oneset.setMbMb(d); break;
		case 6: oneset.setPoleMt(d); break;
		case 7: oneset.setMass(mTau, d); 
		  oneset.setPoleMtau(d); break;
		case 8: break;
		case 11: oneset.setMass(mElectron, d); break;
		case 12: break;
		case 13: oneset.setMass(mMuon, d); break;
		case 14: break;
		case 21: oneset.setMass(mDown, d);
		  break;
		case 22: oneset.setMass(mUp, d); break;
		case 23: oneset.setMass(mStrange, d); break;
		case 24: oneset.setMass(mCharm, d); break;
		default: 
		  cout << "# WARNING: Don't understand data input " << i 
		       << " " << d << " in block "
		       << block << ": ignoring it\n"; break;
		}
	      } 
	      else if (block == "MSQ2IN") {
		modelIdent = "nonUniversal";
		int i, j; double d; kk >> i >> j >> d;
	      }
	      else if (block == "MSU2IN") {
		modelIdent = "nonUniversal";
		int i, j; double d; kk >> i >> j >> d;
	      }
	      else if (block == "MSD2IN") {
		modelIdent = "nonUniversal";
		int i, j; double d; kk >> i >> j >> d;
	      }
	      else if (block == "MSL2IN") {
		modelIdent = "nonUniversal";
		int i, j; double d; kk >> i >> j >> d;
	      }
	      else if (block == "MSE2IN") {
		modelIdent = "nonUniversal";
		int i, j; double d; kk >> i >> j >> d;
	      }
	      else if (block == "TUIN") {
		modelIdent = "nonUniversal";
		int i, j; double d; kk >> i >> j >> d;
		pars((i-1) * 3 + j + 33) = d;
		slha2setTrilinear[(i-1) * 3 + j - 1] = true;
	      }
	      else if (block == "TDIN") {
		modelIdent = "nonUniversal";
		int i, j; double d; kk >> i >> j >> d;
		pars((i-1) * 3 + j + 42) = d;
		slha2setTrilinear[(i-1) * 3 + j + 8] = true;
	      }
	      else if (block == "TEIN") {
		modelIdent = "nonUniversal";
		int i, j; double d; kk >> i >> j >> d;
		pars((i-1) * 3 + j + 51) = d;
		slha2setTrilinear[(i-1) * 3 + j + 17] = true;
	      }
	      else if (block == "RVLAMLLEIN") {
		int i,j,k; double d; kk >> i >> j >> k >> d;
		if ((i > 0 && i <=  3) || (j > 0 && j <=  3) ||
		    (k > 0 && k <=  3)) {
		}
		else {
		  cout << "# WARNING: Don't understand data input " << i 
		       << " " << j << " " << k << " " << d << " in block "
		       << block << ": ignoring it\n"; break;
		}
	      }
	      else if (block == "RVLAMLQDIN") {
		int i,j,k; double d; kk >> i >> j >> k >> d;
		if((i > 0 && i <=  3) || (j > 0 && j <=  3) ||
		   (k > 0 && k <=  3)) {
		}
		else {
		  cout << "# WARNING: Don't understand data input " << i 
		       << " " << j << " " << k << " " << d << " in block "
		       << block << ": ignoring it\n"; break;
		}
	      }
	      else if (block == "RVLAMUDDIN") {
		int i,j,k; double d; kk >> i >> j >> k >> d;
		if((i > 0 && i <=  3) || (j > 0 && j <=  3) || 
		   (k > 0 && k <=  3)) {
		}
	      }
	      else if (block == "RVTIN") {
		int i,j,k; double d; kk >> i >> j >> k >> d;
		if((i > 0 && i <=  3) || (j > 0 && j <=  3) || 
		   (k > 0 && k <=  3)) {
		}
		else {
		  cout << "# WARNING: Don't understand data input " << i 
		       << " " << j << " " << k << " " << d << " in block "
		       << block << ": ignoring it\n"; break;
		}
	      }
	      else if (block == "RVTPIN") {
		int i,j,k; double d; kk >> i >> j >> k >> d;
		if((i > 0 && i <=  3) || (j > 0 && j <=  3) || 
		   (k > 0 && k <=  3)) {
		}
		else {
		  cout << "# WARNING: Don't understand data input " << i 
		       << " " << j << " " << k << " " << d << " in block "
		       << block << ": ignoring it\n"; break;
		}
	      }
	      else if (block == "RVTPPIN") {
		int i,j,k; double d; kk >> i >> j >> k >> d;
		if((i > 0 && i <=  3) || (j > 0 && j <=  3) ||
		   (k > 0 && k <=  3)) {
		}
		else {
		  cout << "# WARNING: Don't understand data input " << i 
		       << " " << j << " " << k << " " << d << " in block "
		       << block << ": ignoring it\n"; break;
		}
	      }
	      else if (block == "RVKAPPAIN") {
		int i; double d; kk >> i >> d;
		if (i > 0 && i <=  3) {
		}
		else {
		  cout << "# WARNING: Don't understand data input " << i << d 
		       << " in block " << block << ": ignoring it\n"; break;
		}
	      }
	      else if (block == "RVDIN") {
		int i; double d; kk >> i >> d;
		if (i > 0 && i <=  3) {
		}
		else {
		  cout << "# WARNING: Don't understand data input " 
		       << i << d << " in block " << block 
		       << ": ignoring it\n"; break;
		}
	      }
	      // input of sneutrino VEVs not supported yet
	      else if (block == "RVSNUVEVIN") {
		int i; double d; kk >> i >> d;
		cout << "# WARNING: in block " << block 
		     << ": SOFTSUSY does not support setting of sneutrino VEVs"
		     << " yet : ignoring them\n"; break;
	      }
	      else if (block == "RVMLH1SQIN") {
		int i; double d; kk >> i >> d;
		if ((i > 0 && i <=  3)) {
		}
		else {
		  cout << "# WARNING: Don't understand data input " 
		       << i << d << " in block " << block 
		       << ": ignoring it\n"; break;
		}
	      }
	      else if (block == "SOFTSUSY") {
		int i; double d; kk >> i >> d;
		switch(i) {
		case 1: TOLERANCE = d; break;
		case 2: 
		  MIXING = int(d); 
		  //if (MIXING > 0) flavourViolation = true;
		  break;
		case 3: PRINTOUT = int(d); break;
		case 4: QEWSB = d; break;
		case 5: INCLUDE_2_LOOP_SCALAR_CORRECTIONS = 
		    bool(int(d+EPSTOL)); break;
		case 6: outputCharacteristics(int(d+EPSTOL)-1); break;  
		case 7: {
		  int num = int(d+EPSTOL);
		  if (num != 1 && num!= 2) {
		    cout << "# WARNING: Can only set number of loops for"
			 << " higgs masses and REWSB to be 1 or 2 in "
			 << " BLOCK SOFTSUSY parameter 7, not " << num 
			 << ". Ignoring.\n";
		  } else {
		    numHiggsMassLoops = num;
		    numRewsbLoops = num;
		  }
		}
		break;
		case 8: {
		  int num = int(d + EPSTOL);
		  if (num != 0 && num != 1) {
		    cout << "# Incorrect flag in BLOCK SOFTSUSY 8: " 
			 << num << ". Ignoring it.\n";
		  } else {
		    if (num == 1) susyRpvBCatMSUSY = true;
		    else susyRpvBCatMSUSY = false;
		  }
		}
		  break;
		case 9: {
		  int num = int(d + EPSTOL);		  
		  if (num != 0 && num != 1) {
		    cout << "# Incorrect flag in BLOCK SOFTSUSY 9: " 
			 << num << ". Ignoring it.\n";
		  } else {
		  }
		}
		  break;
		case 10: {
		  int num = int(d + EPSTOL);
		  if (num != 0 && num != 1) {
		    cout << "# Incorrect flag in BLOCK SOFTSUSY 10: " 
			 << num << ". Ignoring it.\n";
		  } else if (num == 1) forceSlha1 = true;
		  else forceSlha1 = false;
		}
		  break;
		case 11: {
		  /// Set gravitino mass
		  r->setM32(d); 
		}
		  break;
		case 12: {
		  int num = int(d + EPSTOL);
		  if (num == 1) printRuledOutSpectra = true;
		  else if (num == 0) printRuledOutSpectra = false;
		  else cout << "# WARNING: Don't understand Block SOFTSUSY "
			    << "parameter 12 " << d << ". Ignoring it." 
			    << endl;
		}
		  break;
		case 13: {
		  int num = int(d + EPSTOL);
		  if (num == 1) mAFlag = true;		  
		}
		case 14: {
		  int num = int(d + EPSTOL);
		  if (num == 1) tryToConvergeHard = true;		  
		}

		  break;
		default:
		  cout << "# WARNING: Don't understand data input " << i 
		       << " " << d << " in block "
		       << block << ": ignoring it\n"; break;
		}
	      }
	      else {
		cout << "# WARNING: don't recognise block " << block 
		   << ": ignoring all data in it" << endl;
	      }
	      // end if blocks
	      
	    } // end of data
	  } // end of no-comment
	  
	} // end of file
	
      }
      else errorCall();
    }

    if (r->displayAltEwsb()) {
      if (modelIdent != "splitgmsb") {
	//	boundaryCondition = &extendedSugraBcs2;
	r->setSusyMu(pars(23)); 
      } else {
	ostringstream ii;
	ii << "Split GMSB BCs should not supported with alternative EWSB\n";
	throw ii.str();
	/// Split GMSB BCs: different
	/*	r->setSusyMu(400.);
	r->setMuCond(400.);
	r->setMaCond(400.);*/
      }
      sgnMu = 0; // Flags different BCs
    }

    // set NMSSM boundary conditions
    if (susy_model == NMSSM) {
       if (flavourViolation) {
          string msg("# Error: flavour violation in the NMSSM is currenty"
                     " not supported\n");
          throw msg;
       }
       if (modelIdent == "sugra") {
          nmssmBoundaryCondition = &NmssmMsugraBcs;
          if (pars.size() != 3)
             pars.setEnd(3);
       } else if (modelIdent == "nonUniversal") {
          nmssmBoundaryCondition = &extendedNMSugraBcs;
          if (pars.size() != 53) {
             string msg("# Error: NMSSM non-minmal sugra boundary condition"
                        " chosen, but pars does not have 53 entries\n");
             throw msg;
          }
       } else {
          string msg("# Error: non-sugra boundary conditions for the NMSSM"
                     " are currently not supported\n");
          throw msg;
       }
    }

    int pos = 10;
    if (RPVflag) {
       cout << "# WARNING: there is no RPV version for selected "
            << " boundary condition!" << endl;
    }
    // intput error checking  
    if (sgnMu != 1 && sgnMu != -1 && sgnMu != 0) {
      ostringstream ii;
      ii << "Incorrect input for sign(mu)=" << sgnMu <<endl;
      throw ii.str();
    }
    if (tanb < 1.0 || tanb > 5.0e2)  {
      ostringstream ii;
      ii << "Incorrect input for tan beta=" << tanb <<endl;
      throw ii.str();
    }
    
    oneset.toMz();

    /// Initial guess for mu
    //    double muFirst = 1000.;
    //    r->setSusyMu(muFirst);

    switch (susy_model) {
    case MSSM:
       r->lowOrg(boundaryCondition, mgutGuess, pars, sgnMu,
                 tanb, oneset, gaugeUnification, ewsbBCscale);
       /// Fix to mh if additional operators are assumed
       if (desiredMh > 0.1) {
          sPhysical s(r->displayPhys()); s.mh0(1) = desiredMh; r->setPhys(s);
       }
       r->lesHouchesAccordOutput(cout, modelIdent.c_str(), pars, sgnMu, tanb, qMax,
                                 numPoints, ewsbBCscale);
       if (r->displayProblem().test()) {
          cout << "# SOFTSUSY problem with point: " << r->displayProblem() << endl;
       }
       break;
    case NMSSM: {
       nmssm_input.check_setup();

       softsusy::Z3 = nmssm_input.is_Z3_symmetric();

       DoubleVector nmpars(nmssm_input.get_nmpars());
       nmssm.lowOrg(nmssmBoundaryCondition, mgutGuess, pars, nmpars, sgnMu,
                    tanb, oneset, gaugeUnification, ewsbBCscale);
       nmssm.lesHouchesAccordOutput(cout, modelIdent.c_str(), pars, sgnMu, tanb, qMax,
                                    numPoints, ewsbBCscale);
       if (nmssm.displayProblem().test()) {
          cout << "# SOFTSUSY problem with NMSSM point: "
               << nmssm.displayProblem() << endl;
       }
       }
       break;
    default:
       cout << "# Error: unknown susy model " << susy_model
            << ", please check your MODSEL (entry 3) settings" << endl;
       break;
    }
  }
  catch(const string & a) { cout << a; return -1; }
  catch(const char * a) { cout << a; return -1; }
  catch(...) { cout << "Unknown type of exception caught.\n"; return -1; }
  
  return 0;
}

