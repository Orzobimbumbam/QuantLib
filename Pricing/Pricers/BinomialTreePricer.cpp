//
// Created by Alberto Campi on 21/07/2018.
//

#include "BinomialTreePricer.h"

pricing::BinomialTreePricer::BinomialTreePricer(const pricing::Option &optionStyle, const pricing::PayOff &payOff,
                                                const pricing::TreeModel &moveModel, unsigned long nPeriods,
                                                double spot, const common::MoneyMarketAccount &discountCurve) :
        RecombiningTreePricer(optionStyle, payOff, moveModel, nPeriods), m_spot(spot), m_mma(discountCurve) {}

pricing::BinomialTreePricer::BinomialTreePricer(const pricing::Option &optionStyle, const pricing::PayOff &payOff,
                                                const pricing::TreeModel &moveModel, const pricing::OptionEvent &event,
                                                unsigned long nPeriods, double spot,
                                                const common::MoneyMarketAccount &discountCurve) :
        RecombiningTreePricer(optionStyle, payOff, moveModel, nPeriods, event), m_spot(spot), m_mma(discountCurve) {}

bool pricing::BinomialTreePricer::isArbitrage() const
{
    const double tau = m_optionStyle -> getOptionYearsToMaturity()/m_nPeriods;
    const double intraPeriodRiskFreeGrowth = 1./m_mma(tau);

    return !(intraPeriodRiskFreeGrowth < m_upMove && intraPeriodRiskFreeGrowth > m_downMove);
}

double pricing::BinomialTreePricer::getRiskNeutralProbUpMove() const
{
    const double tau = m_optionStyle -> getOptionYearsToMaturity()/m_nPeriods;
    const double intraPeriodRiskFreeGrowth = 1./m_mma(tau);

    return (intraPeriodRiskFreeGrowth - m_downMove)/(m_upMove - m_downMove);
}

double pricing::BinomialTreePricer::getSpotPriceAtNode(unsigned long stepIndex, unsigned long outcomeIndex) const
{
    return m_spot*pow(m_upMove, stepIndex)*pow(m_downMove, outcomeIndex);
}

double pricing::BinomialTreePricer::optionPrice() const
{
    if (!isArbitrage())
    {
        std::vector<double> runningPayOffs(m_nPeriods + 1);
        boost::gregorian::date T = m_optionStyle -> getOptionDate().getMaturityDate();

        for (unsigned long i = 0; i <= m_nPeriods; ++i)
        {
            const double finalSpot = getSpotPriceAtNode(i, m_nPeriods - i);
            const PathMap finalSpotAsMap = {{T, getSpotPriceAtNode(i, m_nPeriods - i)}};

            //handle potential option events in the final payoffs
            if (!m_optionEvent && m_optionEvent -> optionEventHasOccurred(finalSpot))
                runningPayOffs[i] = m_optionEvent -> getPayOffAtOptionEvent(finalSpotAsMap);
            else
                runningPayOffs[i] = m_optionPayOff -> payOff(finalSpotAsMap);
        }

        const double qu = getRiskNeutralProbUpMove(), qd = 1 - qu;
        for (long i = m_nPeriods; i > 0; --i) //backward induction
        {
            for (unsigned long j = 0; j < i; ++j)
            {
                const double spot = getSpotPriceAtNode(i, j);
                const PathMap spotAsMap = {{T, spot}}; //TODO: T here is wrong, should work out the exact date

                //handle potential option events in the underlying asset
                if (!m_optionEvent && m_optionEvent -> optionEventHasOccurred(spot))
                    runningPayOffs[j] = m_optionEvent -> getPayOffAtOptionEvent(spotAsMap);
                else
                    runningPayOffs[j] = qd*runningPayOffs[j] + qu*runningPayOffs[j+1];
            }
        }

        return m_mma(m_optionStyle -> getOptionYearsToMaturity())*runningPayOffs[0];
    }
    else
        throw std::invalid_argument("pricing::BinomialTreePricer::optionPrice : Invalid data. \n"
                                    "Arbitrage in the market.");

}