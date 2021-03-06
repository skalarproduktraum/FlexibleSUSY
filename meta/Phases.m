
BeginPackage["Phases`", {"TextFormatting`", "CConversion`"}];

ConvertSarahPhases::usage="convert SARAH phases to our format";

CreatePhasesDefinition::usage="creates definitions of the phases";

CreatePhasesGetterSetters::usage="creates function definitions
for phase getters and setters";

CreatePhasesInitialization::usage="creates initialization list of
phases"

Begin["`Private`"];

ConvertSarahPhases[phases_List] :=
    DeleteDuplicates[(#[[2]])& /@ phases];

CreatePhasesDefinition[phases_List] :=
    Module[{result = "", k},
           For[k = 1, k <= Length[phases], k++,
               result = result <> CConversion`CreateCType[
                            CConversion`ScalarType[
                                CConversion`complexScalarCType]] <> " " <>
                        ToValidCSymbolString[phases[[k]]] <> ";\n";
              ];
           Return[result];
          ];

CreatePhasesGetterSetters[phases_List] :=
    Module[{result = "", k, phaseName, type},
           For[k = 1, k <= Length[phases], k++,
               phaseName = ToValidCSymbolString[phases[[k]]];
               type = CConversion`CreateCType[CConversion`ScalarType[CConversion`complexScalarCType]];
               result = result <>
                        CConversion`CreateInlineSetter[phaseName, "const " <> type <> "&"] <>
                        CConversion`CreateInlineGetter[phaseName, "const " <> type <> "&"];
              ];
           Return[result];
          ];

CreatePhasesInitialization[phases_List] :=
    Module[{result = "", k, phaseName},
           For[k = 1, k <= Length[phases], k++,
               phaseName = ToValidCSymbolString[phases[[k]]];
               result = result <> ", " <> phaseName <> "(1,0)";
              ];
           Return[result];
          ];

End[];

EndPackage[];
