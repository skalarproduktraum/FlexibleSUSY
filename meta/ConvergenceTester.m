
BeginPackage["ConvergenceTester`", {"CConversion`", "TextFormatting`", "TreeMasses`"}];

CreateCompareFunction::usage="";

Begin["`Private`"];

CountNumberOfMasses[particles_List] :=
    Plus @@ (TreeMasses`GetDimension /@ particles);

CountNumberOfMasses[particle_] :=
    TreeMasses`GetDimension[particle];

CalcDifference[particle_, offset_Integer, diff_String] :=
    Module[{result, body, dim, dimStart, esStr},
           dim = TreeMasses`GetDimension[particle];
           esStr = ToValidCSymbolString[FlexibleSUSY`M[particle]];
           If[dim == 1,
              result = diff <> "[" <> ToString[offset] <> "] = " <>
                       "MaxRelDiff(OLD1(" <> esStr <> "),NEW1(" <> esStr <> "));\n";
              ,
              dimStart = TreeMasses`GetDimensionStartSkippingGoldstones[particle] - 1;
              result = "for (unsigned i = " <> ToString[dimStart] <>
                       "; i < " <> ToString[dim] <> "; ++i) {\n";
              body = diff <> "[i + " <> ToString[offset] <> "] = " <>
                     "MaxRelDiff(OLD(" <> esStr <> ",i),NEW(" <> esStr <> ",i));";
              result = result <> IndentText[body] <> "\n}\n";
             ];
           Return[result];
          ];

CreateCompareFunction[particles_List] :=
    Module[{result, numberOfMasses, i, offset = 0, massiveSusyParticles},
           massiveSusyParticles = Select[particles /. FlexibleSUSY`M -> Identity,
                                         (!TreeMasses`IsMassless[#] && !SARAH`SMQ[#])&];
           numberOfMasses = CountNumberOfMasses[massiveSusyParticles];
           If[numberOfMasses == 0,
              Print["Warning: model has no massive susy particles!"];
              Return["return 0.;"];
             ];
           result = "double diff[" <> ToString[numberOfMasses] <> "] = { 0 };\n\n";
           For[i = 1, i <= Length[massiveSusyParticles], i++,
               result = result <> CalcDifference[massiveSusyParticles[[i]], offset, "diff"];
               offset += CountNumberOfMasses[massiveSusyParticles[[i]]];
              ];
           If[offset != numberOfMasses,
              Print["Error: something is wrong with the counting of masses:"];
              Print["  numberOfMasses = ", numberOfMasses, ", offset = ", offset];
             ];
           result = result <>
                    "\nreturn *std::max_element(diff, diff + " <>
                    ToString[numberOfMasses] <> ");\n";
           Return[result];
          ];

End[];

EndPackage[];
