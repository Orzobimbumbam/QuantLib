//
// Created by Alberto Campi on 21/07/2018.
//

#include "BinomialTreePricer.h"

pricing::BinomialTreePricer::BinomialTreePricer(const pricing::Option &option, const pricing::TreeModel &moveModel,
                                                double spot, const common::MoneyMarketAccount &discountCurve) :
        RecombiningTreePricer(option, moveModel),
        m_spot(spot), m_mma(discountCurve), m_tau(m_option -> getOptionYearsToMaturity()/m_nPeriods) {}

pricing::BinomialTreePricer::BinomialTreePricer(const pricing::Option &option, const pricing::TreeModel &moveModel,
                                                const pricing::OptionEvent &event,
                                                double spot, const common::MoneyMarketAccount &discountCurve) :
        RecombiningTreePricer(option, moveModel, event),
        m_spot(spot), m_mma(discountCurve), m_tau(m_option -> getOptionYearsToMaturity()/moveModel.getNPeriods()) {}

bool pricing::BinomialTreePricer::isArbitrage() const
{
    const double intraPeriodRiskFreeGrowth = 1./m_mma(m_tau);
    return !(intraPeriodRiskFreeGrowth < m_upMove && intraPeriodRiskFreeGrowth > m_downMove);
}

double pricing::BinomialTreePricer::getRiskNeutralProbUpMove() const
{
    //const double tau = m_optionStyle -> getOptionYearsToMaturity()/m_nPeriods;
    const double intraPeriodRiskFreeGrowth = 1./m_mma(m_tau);

    return (intraPeriodRiskFreeGrowth - m_downMove)/(m_upMove - m_downMove);
}

double pricing::BinomialTreePricer::getSpotPriceAtNode(unsigned long stepIndex, unsigned long outcomeIndex) const
{
    return m_spot*pow(m_upMove, outcomeIndex)*pow(m_downMove, stepIndex - outcomeIndex);
}

double pricing::BinomialTreePricer::optionPrice() const
{
    if (!isArbitrage())
    {
        std::vector<double> runningPayOffs(m_nPeriods + 1);
        boost::gregorian::date T = m_option -> getOptionDate().getMaturityDate();

        for (unsigned long i = 0; i <= m_nPeriods; ++i)
        {
            const double finalSpot = getSpotPriceAtNode(m_nPeriods, i);
            const PathMap finalSpotAsMap = {{T, finalSpot}};

            //handle potential option events in the final payoffs
            if (m_optionEvent != nullptr && m_optionEvent -> optionEventHasOccurred(finalSpot))
            {
                runningPayOffs[i] = m_optionEvent -> getPayOffAtOptionEvent(finalSpotAsMap);
                m_optionEvent -> resetAllFlags();
            }
            else
                runningPayOffs[i] = m_option -> getOptionPayOff(finalSpotAsMap);
        }

        const double qu = getRiskNeutralProbUpMove(), qd = 1 - qu;
        //const double tau = m_optionStyle -> getOptionYearsToMaturity()/m_nPeriods;
        const unsigned long tauInDays = m_option -> getOptionDate().getDurationLengthInDays(m_tau);
        for (long i = m_nPeriods - 1; i >= 0; --i) //backward induction up to zeroth node (t = 0)
        {
            for (unsigned long j = 0; j <= i; ++j)
            {
                const double spot = getSpotPriceAtNode(i, j);
                const PathMap spotAsMap = {{T, spot}};
                T -= boost::gregorian::days(tauInDays); //roll T backwards by tau in days after each step on the tree

                //handle potential option events in the underlying asset
                if (m_optionEvent != nullptr && m_optionEvent -> optionEventHasOccurred(spot))
                {
                    runningPayOffs[j] = m_optionEvent -> getPayOffAtOptionEvent(spotAsMap);
                    m_optionEvent -> resetAllFlags();
                }
                else
                    runningPayOffs[j] = qd*runningPayOffs[j] + qu*runningPayOffs[j+1];
            }
        }

        return m_mma(m_option -> getOptionYearsToMaturity())*runningPayOffs[0];
    }
    else
        throw std::invalid_argument("pricing::BinomialTreePricer::optionPrice : Invalid data. \n"
                                    "Arbitrage in the market.");

}
 void pricing::BinomialTreePricer::setMoveModel(const pricing::TreeModel &moveModel)
 {
     pricing::RecombiningTreePricer::setMoveModel(moveModel);
     m_tau = m_option -> getOptionYearsToMaturity()/m_nPeriods;
 }