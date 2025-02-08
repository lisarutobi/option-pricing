#include <iostream>
#include <vector>
#include "CallOption.h"
#include "PutOption.h"
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"
#include "AsianCallOption.h"
#include "AsianPutOption.h"
#include "BlackScholesMCPricer.h"
#include <iostream>
#include <iostream>
#include "AmericanCallOption.h"
#include "AmericanPutOption.h"
#include "CallOption.h"
#include "PutOption.h"
#include "CRRPricer.h"
#include <iostream>
#include "AmericanCallOption.h"
#include "AmericanPutOption.h"
#include "CRRPricer.h"
#include <iostream>
#include "AmericanCallOption.h"
#include "CRRPricer.h"
#include <iostream>
#include "CRRPricer.h"
#include "AmericanCallOption.h"
#include <iostream>
#include "CRRPricer.h"
#include "AmericanCallOption.h"
#include <iostream>
#include "BlackScholesPricer.h"
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"
#include "EuropeanVanillaOption.h"
#include <iostream>
#include "CRRPricer.h"
#include "AmericanCallOption.h"
#include <iostream>
#include "CRRPricer.h"
#include "AmericanCallOption.h"
#include <iostream>
#include <iostream>
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"
#include "BlackScholesPricer.h"
#include <iostream>
#include "PutOption.h"
#include "BlackScholesMCPricer.h"
#include <iostream>
#include "CRRPricer.h"
#include "AmericanCallOption.h"

#include <iostream>
#include "CallOption.h"
#include "BlackScholesMCPricer.h"
#include "CRRPricer.h"
#include "AmericanCallOption.h"
#include <iostream>
#include "CRRPricer.h"
#include <iostream>
#include <vector>
#include "BlackScholesMCPricer.h"
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"<^$*²

#include "AsianCallOption.h"
#include "AsianPutOption.h"
// On suppose que l'enum class optionType { Call, Put }; est défini dans un header inclus par Option.h
#include <iostream>
#include "Option.h"
#include "CallOption.h"
#include "CRRPricer.h"

#include "BlackScholesMCPricer.h"
#include "AsianOption.h"
#include <iostream>
#include <vector>
#include <memory>
#include <iostream>
#include <vector>
#include "BlackScholesMCPricer.h"
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"
#include "AsianCallOption.h"
#include "AsianPutOption.h"
// On suppose que l'enum class optionType { Call, Put }; est défini dans un header inclus par Option.h
int main() {
    // -----------------------------
    // Paramètres généraux
    // -----------------------------
    double S0 = 100.0;   // Spot initial
    double K = 101.0;   // Strike
    double T = 5.0;     // Maturité (5 ans)
    double r = 0.01;    // Taux d'intérêt
    double vol = 0.1;     // Volatilité

    // -----------------------------
    // Création d'options européennes
    // -----------------------------
    // Call / Put vanille
    EuropeanVanillaOption europeanCall(T, K, optionType::Call);
    EuropeanVanillaOption europeanPut(T, K, optionType::Put);

    // Digital Call / Put
    EuropeanDigitalCallOption digitalCall(T, K);
    EuropeanDigitalPutOption  digitalPut(T, K);

    // -----------------------------
    // BLACK-SCHOLES
    // -----------------------------
    std::cout << "======== Pricing via Black-Scholes ========" << std::endl;
    {
        // Call Vanille
        BlackScholesPricer bsCall(&europeanCall, S0, r, vol);
        double callPriceBS = bsCall();
        std::cout << "European Vanilla Call (BS) = " << callPriceBS << std::endl;

        // Put Vanille
        BlackScholesPricer bsPut(&europeanPut, S0, r, vol);
        double putPriceBS = bsPut();
        std::cout << "European Vanilla Put  (BS) = " << putPriceBS << std::endl;

        // Digital Call
        BlackScholesPricer bsDigCall(&digitalCall, S0, r, vol);
        double digCallPriceBS = bsDigCall();
        std::cout << "European Digital Call (BS) = " << digCallPriceBS << std::endl;

        // Digital Put
        BlackScholesPricer bsDigPut(&digitalPut, S0, r, vol);
        double digPutPriceBS = bsDigPut();
        std::cout << "European Digital Put  (BS) = " << digPutPriceBS << std::endl;
    }
    std::cout << std::endl;

    // -----------------------------
    // CRR (U=0.05, D=-0.045, R=0.01, N=5)
    // -----------------------------
    std::cout << "======== Pricing via CRR (N=5, U=0.05, D=-0.045, R=0.01) ========" << std::endl;
    {
        int    N = 5;
        double U = 0.05;
        double D = -0.045;
        double R = 0.01; // Interprété comme 'taux par step', i.e. 1+R

        // Call Vanille
        CRRPricer crrCall(&europeanCall, N, S0, U, D, R);
        double callPriceCRR = crrCall();
        std::cout << "European Vanilla Call (CRR) = " << callPriceCRR << std::endl;

        // Put Vanille
        CRRPricer crrPut(&europeanPut, N, S0, U, D, R);
        double putPriceCRR = crrPut();
        std::cout << "European Vanilla Put  (CRR) = " << putPriceCRR << std::endl;

        // Digital Call
        CRRPricer crrDigCall(&digitalCall, N, S0, U, D, R);
        double digCallPriceCRR = crrDigCall();
        std::cout << "European Digital Call (CRR) = " << digCallPriceCRR << std::endl;

        // Digital Put
        CRRPricer crrDigPut(&digitalPut, N, S0, U, D, R);
        double digPutPriceCRR = crrDigPut();
        std::cout << "European Digital Put  (CRR) = " << digPutPriceCRR << std::endl;
    }
    std::cout << std::endl;

    // -----------------------------
    // MONTE CARLO
    // -----------------------------
    std::cout << "======== Pricing via Monte Carlo ========" << std::endl;
    {
        // Nombre de chemins demandés
        int nbPaths = 1'000'000;

        // 1) Options européennes (Vanille ou Digital)
        //    Les options européennes non-asiatiques ont un vecteur de fixingDates = { T }
        //    => On peut toujours les pricer en MC avec 1 step.

        // European Call
        BlackScholesMCPricer mcCall(&europeanCall, S0, r, vol);
        mcCall.generate(nbPaths);
        double callPriceMC = mcCall();
        auto ciCall = mcCall.confidenceInterval();
        std::cout << "European Vanilla Call (MC) = " << callPriceMC
            << " | CI 95% = [" << ciCall[0] << ", " << ciCall[1] << "]" << std::endl;

        // European Put
        BlackScholesMCPricer mcPut(&europeanPut, S0, r, vol);
        mcPut.generate(nbPaths);
        double putPriceMC = mcPut();
        auto ciPut = mcPut.confidenceInterval();
        std::cout << "European Vanilla Put  (MC) = " << putPriceMC
            << " | CI 95% = [" << ciPut[0] << ", " << ciPut[1] << "]" << std::endl;

        // Digital Call
        BlackScholesMCPricer mcDigCall(&digitalCall, S0, r, vol);
        mcDigCall.generate(nbPaths);
        double digCallPriceMC = mcDigCall();
        auto ciDigCall = mcDigCall.confidenceInterval();
        std::cout << "European Digital Call (MC) = " << digCallPriceMC
            << " | CI 95% = [" << ciDigCall[0] << ", " << ciDigCall[1] << "]" << std::endl;

        // Digital Put
        BlackScholesMCPricer mcDigPut(&digitalPut, S0, r, vol);
        mcDigPut.generate(nbPaths);
        double digPutPriceMC = mcDigPut();
        auto ciDigPut = mcDigPut.confidenceInterval();
        std::cout << "European Digital Put  (MC) = " << digPutPriceMC
            << " | CI 95% = [" << ciDigPut[0] << ", " << ciDigPut[1] << "]" << std::endl;

        std::cout << std::endl;

        // 2) Options asiatiques : on crée 50 dates de fixations entre 0 et T
        //    (excluant 0, incluant T). Libre à vous de choisir la granularité.
        //    On suppose que vous avez des classes AsianCallOption, AsianPutOption
        //    héritant de AsianOption, et donc de Option.
        std::vector<double> fixingDates;
        int nbFixings = 50;
        double dt = T / nbFixings;
        for (int i = 1; i <= nbFixings; ++i) {
            fixingDates.push_back(i * dt); // Par ex : 0.1, 0.2, ... 5.0
        }

        // Asian Call
        AsianCallOption asianCall(fixingDates, K);
        BlackScholesMCPricer mcAsianCall(&asianCall, S0, r, vol);
        mcAsianCall.generate(nbPaths);
        double asianCallPriceMC = mcAsianCall();
        auto ciAsianCall = mcAsianCall.confidenceInterval();
        std::cout << "Asian Call (MC)        = " << asianCallPriceMC
            << " | CI 95% = [" << ciAsianCall[0] << ", " << ciAsianCall[1] << "]" << std::endl;

        // Asian Put
        AsianPutOption asianPut(fixingDates, K);
        BlackScholesMCPricer mcAsianPut(&asianPut, S0, r, vol);
        mcAsianPut.generate(nbPaths);
        double asianPutPriceMC = mcAsianPut();
        auto ciAsianPut = mcAsianPut.confidenceInterval();
        std::cout << "Asian Put (MC)         = " << asianPutPriceMC
            << " | CI 95% = [" << ciAsianPut[0] << ", " << ciAsianPut[1] << "]" << std::endl;
    }

    return 0;
}