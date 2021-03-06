ParticleDefinitions[GaugeES] = {
      {SdL0,       { Description -> "Left Down-Squarks"}},
      {SdR0,       { Description -> "Right Down-Squarks"}},
      {SuL0,       { Description -> "Left Up-Squarks"}},
      {SuR0,       { Description -> "Right Up-Squarks" }},
      {SeL0,       { Description -> "Left Selectron"}},
      {SeR0,       { Description -> "Right Selectron"}},
      {SvL0,       { Description -> "Left Sneutrino"}},

      {SxL,        { Description -> "Left SExotics",
                     RParity -> 1,
	             FeynArtsNr -> 666,
	             LaTeX -> "\\tilde{x}_L"}},
      {SxR,        { Description -> "Right SExotics",
                     RParity -> 1,
	             FeynArtsNr -> 667,
	             LaTeX -> "\\tilde{x}_R"}},

      {SHd0,       { Description -> "Neutral Down-Higgs",
		     LaTeX -> "h_{13}^0"}},
      {SHdm,       { Description -> "Charged Down-Higgs",
		     LaTeX -> "h_{13}^-"}},
      {SHu0,       { Description -> "Neutral Up-Higgs",
		     LaTeX -> "h_{23}^0"}},
      {SHup,       { Description -> "Charged Up-Higgs",
		     LaTeX -> "h_{23}^+"}},

      {SHd0Inert,  { Description -> "Neutral Inert-Down-Higgs",
  		     RParity -> 1,
  		     FeynArtsNr -> 101,
  		     LaTeX -> "h^{0Inert}_{1}"}},
      {SHdmInert,  { Description -> "Charged Inert-Down-Higgs",
  		     RParity -> 1,
  		     FeynArtsNr -> 102,
  		     LaTeX -> "h^{-Inert}_{1}"}},
      {SHu0Inert,  { Description -> "Neutral Inert-Up-Higgs",
  		     RParity -> 1,
  		     FeynArtsNr -> 103,
  		     LaTeX -> "h^{0Inert}_{2}"}},
      {SHupInert,  { Description -> "Charged Inert-Up-Higgs",
  		     RParity -> 1,
  		     FeynArtsNr -> 104,
  		     LaTeX -> "h^{+Inert}_{2}"}},
      {SSRInert,   { Description -> "Inert-Singlet",
  		     RParity -> 1,
  		     FeynArtsNr -> 105,
  		     LaTeX -> "s^{Inert}",
		     OutputName -> "SSI"}},
      {FSRInert,   { Description -> "Inert-Singlino",
  		     RParity -> -1,
  		     FeynArtsNr -> 106,
  		     LaTeX -> "\\tilde{S}^{Inert}",
		     OutputName -> "FSI"}},

      {H0I1,    { Description -> "Neutral Inert-down-Higgsinos",
                     RParity -> -1,
                     Width -> 0,
                     FeynArtsNr -> 721,
                     LaTeX -> "\\tilde{h}^{0,Inert}_1",
		    OutputName -> "HNI1"}},
      {HCI1,    { Description -> "Charged Inert-down-Higgsinos",
                     RParity -> -1,
                      Width -> 0,
                     FeynArtsNr -> 722,
                     LaTeX -> "\\tilde{h}^{-,Inert}_1",
		    OutputName -> "HCI1"}},
      {H0I2,    { Description -> "Neutral  Inert-up-Higgsinos",
                     RParity -> -1,
                     Width -> 0,
                     FeynArtsNr -> 723,
                     LaTeX -> "\\tilde{h}^{0,Inert}_2",
		    OutputName -> "HNI2"}},
      {HCI2,    { Description -> "Charged Inert-up-Higgsinos",
                     RParity -> -1,
                     Width -> 0,
                     FeynArtsNr -> 724,
                     LaTeX -> "\\tilde{h}^{+}_2",
		    OutputName -> "HCI2"}},

      {VB,         { Description -> "B-Boson"}},
      {VG,         { Description -> "Gluon"}},
      {VWB,        { Description -> "W-Bosons"}},

      {gB,         { Description -> "B-Boson Ghost"}},
      {gG,         { Description -> "Gluon Ghost" }},
      {gWB,        { Description -> "W-Boson Ghost"}},

      {Glu,        { Description -> "Gluino"}},
      {Wino,       { Description -> "Wino"}},
      {Bino,       { Description -> "Bino"}},
      {H01,        { Description -> "Neutral down Higgsinos",
		     RParity -> -1,
		     FeynArtsNr -> 122,
		     LaTeX -> "\\tilde{H}^0_1",
		     OutputName -> "H01"}},
      {HC1,         { Description -> "Charged down Higgsinos",
		      RParity -> -1,
		      FeynArtsNr -> 123,
		      LaTeX -> "\\tilde{H}^-_1",
		      OutputName -> "HC1"}},
      {H02,         { Description -> "Neutral up Higgsinos",
		      RParity -> -1,
		      FeynArtsNr -> 124,
		      LaTeX -> "\\tilde{H}^0_2",
		      OutputName -> "H02"}},
      {HC2,         { Description -> "Charged up Higgsinos",
		      RParity -> -1,
		      FeynArtsNr -> 125,
		      LaTeX -> "\\tilde{H}^+_2",
		      OutputName -> "HC2"}},
      {SSR,        { Description -> "Singlet",
  		     RParity -> 1,
  		     FeynArtsNr -> 705,
  		     LaTeX -> "s_3",
		     OutputName -> "SS3"}},
      {FSR,        { Description -> "Singlino",
  		     RParity -> -1,
  		     FeynArtsNr -> 805,
  		     LaTeX -> "\\tilde{s}_3",
		     OutputName -> "FS3"}},
      {FS1,        { Description -> "Dirac Left Singlino",
  		     RParity -> -1,
		     FeynArtsNr -> 806,
  		     LaTeX -> "\\tilde{s}_L",
		     OutputName -> "FSL"}},
      {FS2,        { Description -> "Dirac Right Singlino",
  		     RParity -> -1,
		     FeynArtsNr -> 807,
  		     LaTeX -> "\\tilde{s}_R",
		     OutputName -> "FSR"}},

      {Fd1,        { Description -> "Dirac Left Down-Quark"}},
      {Fd2,        { Description -> "Dirac Right Down-Quark"}},
      {Fu1,        { Description -> "Dirac Left Up-Quark"}},
      {Fu2,        { Description -> "Dirac Right Up-Quark"}},
      {Fe1,        { Description -> "Dirac Left Electron"}},
      {Fe2,        { Description -> "Dirac Right Electron"}},
      {Fv,         { Description -> "Neutrinos" }},
      {FX1,        { Description -> "Dirac Left Exotics",
		     RParity -> -1,
        	     LaTeX -> "x_1",
		     FeynArtsNr -> 660,
		     OutputName -> "x1"}},
      {FX2,        { Description -> "Dirac Right Exotics",
		     RParity -> -1,
        	     LaTeX -> "x_2",
		     FeynArtsNr -> 661,
		     OutputName -> "x2"}},
      {VU,         { Description -> "Uprime-Boson",
	             RParity -> 1,
	            (* Mass -> LesHouches MassVZprime,*)
	             FeynArtsNr -> 10,
	             LaTeX -> "U'",
		     OutputName -> "Bp"}},
      {gU,         { LaTeX -> "g_U",
		     OutputName -> gU,
		     FeynArtsNr -> 10,
		     RParity -> 1 }},
      {FUprime,        { Description -> "Uprime Neutralino",
			 RParity -> -1,
			 Width -> 0,
			 Mass -> Automatic,
			 FeynArtsNr -> 10,
			 LaTeX -> "\\tilde{U'}",
			 OutputName -> "FBp"}},
      (*added for HiggsPrime*)
      {SHPrime0,   { Description -> "Neutral Prime-Higgs",
      		     RParity -> 1,
      		     FeynArtsNr -> 900,
      		     LaTeX -> "H^{'0}"}},
      {SHPrimem,   { Description -> "Negative charged Prime-Higgs",
      		     RParity -> 1,
      		     FeynArtsNr -> 901,
      		     LaTeX -> "H^{'-}"}},
      {SHBarPrimep,{ Description -> "Positive charged BarPrime-Higgs",
      		     RParity -> 1,
      		     FeynArtsNr -> 902,
      		     LaTeX -> "\\bar{H}^{'+}"}},
      {SHBarPrime0,{ Description -> "Neutral BarPrime-Higgs",
      		     RParity -> 1,
      		     FeynArtsNr -> 903,
      		     LaTeX -> "\\bar{H}^{'0}"}},
      {H0P1,    { Description -> "Neutral Prime-Higgsinos",
                     RParity -> -1,
                     Width -> 0,
                     FeynArtsNr -> 950,
                     LaTeX -> "\\tilde{h}^{'0}_1",
		    OutputName -> "HNP1"}},
      {HCP1,    { Description -> "Charged Prime-Higgsinos",
                     RParity -> -1,
                     Width -> 0,
                     FeynArtsNr -> 951,
                     LaTeX -> "\\tilde{h}^{'-}_1",
		    OutputName -> "HCP1"}},
      {H0P2,    { Description -> "Neutral  Prime-Bar-Higgsinos",
                     RParity -> -1,
                     Width -> 0,
                     FeynArtsNr -> 952,
                     LaTeX -> "\\tilde{\\bar{h}}^{'0}_2",
		    OutputName -> "HNP2"}},
      {HCP2,    { Description -> "Charged Prime-Bar-Higgsinos",
                     RParity -> -1,
                     Width -> 0,
                     FeynArtsNr -> 953,
                     LaTeX -> "\\tilde{\\bar{h}}^{'+}_2",
		    OutputName -> "HCP2"}},
    {FSInert1,    { Description -> "Inert-Singlino-1",
		   RParity -> -1,
		   FeynArtsNr -> 905,
		   LaTeX -> "\\tilde{S}^{Inert}_1",
		   OutputName -> "FSI1"}},
    {FSInert2,    { Description -> "Inert-Singlino-2",
		   RParity -> -1,
		   FeynArtsNr -> 905,
		   LaTeX -> "\\tilde{S}^{Inert}_2",
		   OutputName -> "FSI2"}}
      };

ParticleDefinitions[EWSB] = {
    {Sd,         { Description -> "Down-Squarks",
		   OutputName -> "d"}},
    {Su,         { Description -> "Up-Squarks",
		   OutputName -> "u"}},
    {Se,         { Description -> "Sleptons",
		   OutputName -> "e"}},
    {Sv,       { Description -> "Sneutrinos"}},

    {SX,         { Description -> "SExotics",
		   RParity -> 1,
		   PDG -> {1000051,2000051,1000052,2000052,1000053,2000053},
		   Mass -> Automatic,
		   ElectricCharge -> -1/3,
		   FeynArtsNr -> 666,
		   LaTeX -> "\\tilde{x}",
		   OutputName -> "SX"}},

    {ChiInert,   { Description -> "Inert Neutralinos",
		   RParity -> -1,
		   PDG -> {1000081,1000082,1000083,1000084},
		   Mass -> Automatic,
		   FeynArtsNr -> 13,
		   ElectricCharge -> 0,
		   LaTeX -> "\\tilde{\\chi}^{0,Inert}",
		   OutputName -> "NI"}},

    {ChaInert,   { Description -> "Inert Charginos",
		   RParity -> -1,
		   PDG -> {1000085,1000086},
		   Mass -> Automatic,
		   ElectricCharge -> -1,
		   FeynArtsNr -> 14,
		   LaTeX -> {"\\tilde{\\chi}^{-,Inert}",
			     "\\tilde{\\chi}^{+,Inert}"},
		   OutputName -> "AI"}},
    {FSInert,    { Description -> "Inert-Singlino",
		   RParity -> -1,
		   PDG -> {1000089,1000090},
		   FeynArtsNr -> 105,
		   LaTeX -> "\\tilde{S}^{Inert}",
		   OutputName -> "FSI"}},

    {SH0Inert,   { Description -> "Neutral Inert-Higgs",
		   RParity -> 1,
		   PDG -> {82,86,84,88},
		   FeynArtsNr -> 7,
		   ElectricCharge -> 0,
		   LaTeX -> "h^{0,Inert}",
		   OutputName -> "HNI"}},
    {SHpInert,   { Description -> "Charged Inert-Higgs",
		   RParity -> 1,
		   PDG -> {81,85,83,87},
		   FeynArtsNr -> 8,
		   ElectricCharge -> -1 ,
		   LaTeX -> {"h^{-,Inert}","h^{+,Inert}"},
		   OutputName -> "HCI"}},

    {SS0Inert,   { Description -> "Inert-Singlet",
		   RParity -> 1,
		   PDG -> {89,90},
		   FeynArtsNr -> 105,
		   ElectricCharge -> 0,
		   LaTeX -> "s^{Inert}",
		   OutputName -> "SSI"}},
    {hh,         { Description -> "Higgs",
		   PDG -> {25, 35,45} }},
    {Ah,         { Description -> "Pseudo-Scalar Higgs",
		   LaTeX -> "A",
		   PDG -> {0,0,36},
		   (* FeynArtsNr -> {2,3,4} }}, *)
		   FeynArtsNr -> 2 }},
    {Hpm,        { Description -> "Charged Higgs"}},

    {VP,         { Description -> "Photon"}},
    {gP,         { Description -> "Photon Ghost"}},

    {VZ,         { Description -> "Z-Boson" }},
    {gZ,         { Description -> "Z-Boson Ghost" }},

    {VZprime,    { Description -> "Z'-Boson",
		   RParity -> 1,
		   PDG -> {31},
		   Width -> Automatic,
		   Mass -> LesHouches (*MassVZprime*),
		   FeynArtsNr -> 10,
		   ElectricCharge -> 0,
		   (* Goldstone -> Ah[{2}], *)
		   LaTeX -> "{Z'}",
		   OutputName -> "Zp"}},
    {gZprime,    { Description -> "Z'-Boson Ghost",
		   RParity -> 1,
		   PDG -> 0,
		   Width -> 0,
		   Mass -> Automatic (*Mass[VZprime]*),
		   ElectricCharge -> 0,
		   FeynArtsNr -> 10,
		   LaTeX -> "\\eta_{Z^{'}}",
		   OutputName -> "gZp"}},
    {VG,         { Description -> "Gluon" }},
    {gG,         { Description -> "Gluon Ghost" }},

    {VWm,        { Description -> "W-Boson" }},
    {gWm,        { Description -> "Negative W-Boson Ghost"}},
    {gWmC,       { Description -> "Positive W-Boson Ghost" }},

    {Glu,        { Description -> "Gluino" }},
    {Chi,        { Description -> "Neutralinos",
		   PDG -> {1000022,1000023,1000025,1000035,1000045,1000055},
		   FeynArtsNr -> 11}},
    {Cha,        { Description -> "Charginos",
		   FeynArtsNr -> 12}},

    {Fd,         { Description -> "Down-Quarks",
		   OutputName -> "Fd"}},
    {Fu,         { Description -> "Up-Quarks",
		   OutputName -> "Fu"}},
    {Fe,          { Description -> "Leptons",
		    OutputName -> "Fe"}},
    {Fv,         { Description -> "Neutrinos" }},
    {FX,         { Description->"Exotics",
    		   RParity -> -1,
    		   PDG -> {51,52,53},
    		   Width -> 0,
    		   Mass -> Automatic,
		   ElectricCharge -> -1/3,
    		   FeynArtsNr -> 666,
    		   LaTeX -> "x",
    		   OutputName -> "FX"}},

      (*added for HiggsPrime*)
      {SH0Prime,   { Description -> "Neutral Prime-Higgs",
      		     RParity -> 1,
                     PDG -> {92,94},
      		     FeynArtsNr -> 900,
		     ElectricCharge -> 0,
      		     LaTeX -> "H^{'0}",
		     OutputName -> "HPN"}},
      {SHpPrime,   { Description -> "Charged Prime-Higgs",
      		     RParity -> 1,
                     PDG -> {91,93},
		     ElectricCharge -> -1,
      		     FeynArtsNr -> 901,
      		     LaTeX -> {"H^{'-}","H^{'+}"},
		     OutputName -> "HPA"}},
      {ChiPrime,   { Description -> "Prime Neutralinos",
      		     RParity -> -1,
                     PDG -> {1000092,1000094},
		     ElectricCharge -> 0,
      		     FeynArtsNr -> 900,
      		     LaTeX -> "\\tilde{\\chi}^{'0}",
		     OutputName -> "NP"}},
      {ChaPrime,   { Description -> "Prime Chargino",
      		     RParity -> -1,
                     PDG -> {1000091},
		     ElectricCharge -> -1,
    		     (*Mass -> Automatic,*)
      		     FeynArtsNr -> 901,
      		     LaTeX -> {"\\tilde{\\chi}^{'-}",
      			       "\\tilde{\\chi}^{'+}"},
		     OutputName -> "AP"}}
};



 WeylFermionAndIndermediate = {
      {FHd0,       { Description -> "Neutral Down-Higgsino",
		     LaTeX -> "\\tilde{H}_{13}^0"}},
      {FHu0,       { Description -> "Neutral Up-Higgsino" ,
		     LaTeX -> "\\tilde{H}_{23}^0"}},
      {FHdm,       { Description -> "Charged Down-Higgsino}",
		     LaTeX -> "\\tilde{H}_{13}^-"}},
      {FHup,       { Description -> "Charged Up-Higgsino",
		     LaTeX -> "\\tilde{H}_{23}^+"}},

      {FHPrime0, { Description -> "Neutral Higgsino-Prime",
                     RParity -> -1,
                     FeynArtsNr -> 1053,
                     LaTeX -> "\\tilde{h'}^{0}"}},
      {FHBarPrime0, { Description -> "Neutral Higgsino-Bar-Prime",
                     RParity -> -1,
                     FeynArtsNr -> 1063,
                     LaTeX -> "\\tilde{\\bar{h'}}^{0}"}},
     {FHPrimem, { Description -> "Charged Higgsino-Prime",
                     RParity -> -1,
                     FeynArtsNr -> 1054,
                     LaTeX -> "\\tilde{h'}^{0}"}},
      {FHBarPrimep, { Description -> "Charged Higgsino-Bar-Prime",
                     RParity -> -1,
                     FeynArtsNr -> 1064,
                     LaTeX -> "\\tilde{\\bar{h'}^}{+}"}},
      {FHd0Inert, { Description -> "Neutral Inert-down-Higgsino",
                     RParity -> -1,
                     FeynArtsNr -> 821,
                     LaTeX -> "\\tilde{h}^{0,Inert}_{d}"}},
      {FHu0Inert, { Description -> "Neutral Inert-up-Higgsino",
                     RParity -> -1,
                     FeynArtsNr -> 823,
                     LaTeX -> "\\tilde{h}^{0,Inert}_{u}"}},
     {FHdmInert, { Description -> "Charged Inert-down-Higgsino",
                     RParity -> -1,
                     FeynArtsNr -> 822,
                     LaTeX -> "\\tilde{h}^{-,Inert}_{d}"}},
      {FHupInert, { Description -> "Charged Inert-up-Higgsino",
                     RParity -> -1,
                     FeynArtsNr -> 824,
                     LaTeX -> "\\tilde{h}^{+,Inert}_{u}"}},
    {FS0Inert,    { Description -> "Mixed-Weyl-Inert-Singlino",
		   RParity -> -1,
		   PDG -> {1000089,1000090},
		   FeynArtsNr -> 205,
		   LaTeX -> "\\tilde{S}^{Inert}",
		   OutputName -> "FS0I"}},
      {L0,         { Description -> "Neutralino Weyl-Spinor"}},
      {Lm,         { Description -> "Negative Chargino Weyl-Spinor"}},
      {Lp,         { Description -> "Positive Chargino Weyl-Spinor"}},
      {fG,         { Description -> "Gluino Weyl-Spinor"}},
      {fWB,        { Description -> "Wino Weyl-Spinor"}},
      {fW0,        { Description -> "Neutral Wino" }},
      {fWm,        { Description -> "Negative Wino"}},
      {fWp,        { Description -> "Positive Wino"}},
      {fB,         { Description -> "Bino Weyl-Spinor"}},
      {fU,         { Description -> "UPrimo Weyl-Spinor",
		     LaTeX -> "\\tilde{U}" }},
      {L0Inert,    { Description -> "Neutralino Inert-Weyl-Spinor",
  		     RParity -> -1}},
      {LmInert,    { Description -> "Negative Chargino Inert-Weyl-Spinor",
  		     RParity -> -1}},
      {LpInert,    { Description -> "Positive Chargino Inert-Weyl-Spinor",
  		     RParity -> -1}},
      {L0Prime,    { Description -> "Neutralino Prime-Weyl-Spinor",
  		     RParity -> -1}},

      {phid,       { Description -> "Scalar Down",
		     LaTeX -> "\\phi_{1}"}},
      {phiu,       { Description -> "Scalar Up",
		     LaTeX -> "\\phi_{2}"}},
      {phiS,       { Description -> "Scalar Singlet"}},
      {sigmad,     { Description -> "Pseudo Scalar Down",
		     LaTeX -> "\\sigma_{1}"}},
      {sigmau,     { Description -> "Pseudo Scalar Up",
		     LaTeX -> "\\sigma_{2}"}},
      {sigmaS,     { Description -> "Pseudo Scalar Singlet" }},

      {SHd,        { Description -> "Down-Higgs",
		     LaTeX -> "H_{13}"}},
      {SHu,        { Description -> "Up-Higgs",
		     LaTeX -> "H_{23}"}},
      {Sl,         { Description -> "Left Slepton" }},
      {Sq,         { Description -> "Left Squark" }},
      {SHdInert,   { Description-> "Scalar Inert Down Higgs",
		     LaTeX -> "H^{Inert}_1"}},
      {SHuInert,   { Description-> "Scalar Inert Up Higgs",
		     LaTeX -> "H^{Inert}_2"}},
      {SHPrime,   { Description-> "Scalar Prime Higgs",
		     LaTeX -> "H'"}},
      {SHBarPrime,   { Description-> "Scalar Bar Prime Higgs",
		     LaTeX -> "\\bar{H'}"}},
      {FeL0,       { Description -> "Left Electron" }},
      {FeR0,       { Description -> "Right Electron" }} ,
      {FdL0,       { Description -> "Left Down-Quark" }},
      {FdR0,       { Description -> "Right Down-Quark" }},
      {FuL0,       { Description -> "Left Up-Quark" }},
      {FuR0,       { Description -> "Right Up-Quark" }},
      {FvL0,       { Description -> "Left Neutrino"}},
     {FxL,        { Description -> "Left Exotics",
		     RParity -> -1,
		     LaTeX -> "x_L"}},
     {FxR,        { Description -> "Right Exotics",
		     RParity -> -1,
		     LaTeX -> "x_R"}},
     {FDL,  { Description -> "Rotated Left Up-Quark" }},
       {FDR,  { Description -> "Rotated Right Up-Quark" }},
       {FUL,  { Description -> "Rotated Left Down-Quark"}},
       {FUR,  { Description -> "Rotated Right Down-Quark" }},
       {FEL,  { Description -> "Rotated Left Electron"}},
       {FER,  { Description -> "Rotated Right Electron" }},
     {FXL,          { Description -> "Rotated Left Exotics",
     		     RParity -> -1,
     		     LaTeX -> "X_L"}},
     {FXR,        {Description->"Rotated Right Exotics",
     		     RParity -> -1,
     		     LaTeX -> "X_L"}},
      {FHd,        { Description -> "Down-Higgsino",
		     LaTeX -> "\\tilde{H}_{13}"}},
      {FHu,        { Description -> "Up-Higgsino",
		     LaTeX -> "\\tilde{H}_{23}"}},
      {Fl,         { Description -> "Left Leptons"}},
      {Fq,         { Description -> "Left Quarks"}},
      {FSR,        { Description -> "Weyl Spinor of Singlino"}},
      {FHdInert,   { Description-> "Weyl Inert Down Higgs",
		     LaTeX -> "\\tilde{H}^{Inert}_1"}},
      {FHuInert,   { Description-> "Weyl Inert Up Higgs",
		     LaTeX -> "\\tilde{H}^{Inert}_2"}},
      {FHPrime,   { Description-> "Weyl Prime Higgs",
		     LaTeX -> "\\tilde{H'}"}},
      {FHBarPrime,   { Description-> "Weyl Bar Prime Higgs",
		     LaTeX -> "\\tilde{\\bar{H}}"}},

      {e,          { Description -> "Right Electron Superfield" }},
      {d,          { Description -> "Right Down-Quark Superfield" }},
      {q,          { Description -> "Left Quark Superfield" }},
      {u,          { Description -> "Right Up-Quark Superfield" }},
      {l,          { Description -> "left Lepton Superfield" }},
      {Hd,         { Description -> "Down-Higgs Superfield",
		     LaTeX -> "\\hat{H}_{13}"}},
      {Hu,         { Description -> "Up-Higgs Superfield",
		     LaTeX -> "\\hat{H}_{23}"}},
      {s,          { Description -> "Singlet Superfield",
		     LaTeX -> "\\hat{S}_3"}},
      {G,          { Description -> "Gluon Superfield" }},
      {B,          { Description -> "B Superfield" }},
      {WB,         { Description -> "W Superfield" }},
      {U,          { Description -> "U Superfield",
	             LaTeX -> "\\hat{U}"}},
      {HdInert,    { Description -> "Inert-Down-Higgs Superfield",
		     LaTeX -> "\\hat{H}^{Inert}_{1}"}},
      {HuInert,    { Description -> "Inert-Up-Higgs Superfield",
		     LaTeX -> "\\hat{H}^{Inert}_{2}"}},
      {sInert,     { Description -> "Inert-Singlet Superfield",
		     LaTeX -> "\\hat{S}^{Inert}"}},
      {X,          { Description -> "Left Exotics Superfield",
		     LaTeX -> "\\hat{X}"}},
      {XBar,       { Description -> "Right Exotics Superfield",
		     LaTeX -> "\\hat{\\bar{X}}"}},
      {HPrime,          { Description -> "HPrime Superfield",
                     LaTeX -> "\\hat{H'}"}},
      {HBarPrime,       { Description -> "HPrimeBar Superfield",
                     LaTeX -> "\\hat{\\bar{H'}}"}}
};
