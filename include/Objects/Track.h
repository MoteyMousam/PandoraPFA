/**
 *  @file   PandoraPFANew/include/Objects/Track.h
 * 
 *  @brief  Header file for the track class.
 * 
 *  $Log: $
 */
#ifndef TRACK_H
#define TRACK_H 1

#include "Api/PandoraApi.h"

#include "Pandora/PandoraInternal.h"

namespace pandora
{

/**
 *  @brief  Track class
 */
class Track 
{
public:
    /**
     *  @brief  Operator< now orders by track momentum
     * 
     *  @param  rhs track to compare with
     */
    bool operator< (const Track &rhs) const;

    /**
     *  @brief  Sort tracks by descending energy at dca
     * 
     *  @param  pLhs address of first track
     *  @param  pRhs address of second track
     */
    static bool SortByEnergy(const Track *const pLhs, const Track *const pRhs);

    /**
     *  @brief  Get the 2D impact parameter wrt (0,0)
     * 
     *  @return the 2D impact parameter wrt (0,0)
     */
    float GetD0() const;

    /**
     *  @brief  Get the z coordinate at the 2D distance of closest approach
     * 
     *  @return the z coordinate at the 2D distance of closest approach
     */
    float GetZ0() const;

    /**
     *  @brief  Get the charge sign of the tracked particle, units GeV
     * 
     *  @return the charge sign of the tracked particle
     */
    int GetChargeSign() const;

    /**
     *  @brief  Get the mass of the tracked particle, units GeV
     * 
     *  @return the mass of the tracked particle
     */
    float GetMass() const;

    /**
     *  @brief  Get the track momentum at the 2D distance of closest approach
     * 
     *  @return the track momentum at the 2D distance of closest approach
     */
    const CartesianVector &GetMomentumAtDca() const;

    /**
     *  @brief  Get the track energy at the 2D distance of closest approach
     * 
     *  @return the track energy at the 2D distance of closest approach
     */
    float GetEnergyAtDca() const;

    /**
     *  @brief  Get the track state at the start of the track
     * 
     *  @return the track state at the start of the track
     */
    const TrackState &GetTrackStateAtStart() const;

    /**
     *  @brief  Get the track state at the end of the track
     * 
     *  @return the track state at the end of the track
     */
    const TrackState &GetTrackStateAtEnd() const;

    /**
     *  @brief  Get the (sometimes projected) track state at the ecal
     * 
     *  @return the track state at the ecal
     */
    const TrackState &GetTrackStateAtECal() const;

    /**
     *  @brief  Whether the track reaches the ecal
     * 
     *  @return boolean
     */
    bool ReachesECal() const;

    /**
     *  @brief  Get the list of calorimeter track state projections
     * 
     *  @return address of the list of calorimeter track state projections
     */
    const TrackStateList &GetCalorimeterProjections() const;

    /**
     *  @brief  Get the helix fit to the ecal track state
     * 
     *  @return address of the helix fit to the ecal track state
     */
    const Helix *const GetHelixFitAtECal() const;

    /**
     *  @brief  Whether the track has an associated cluster
     * 
     *  @return boolean
     */
    bool HasAssociatedCluster() const;

    /**
     *  @brief  Get address of the cluster associated with the track
     * 
     *  @param  pCluster to receive the address of the cluster
     */
    StatusCode GetAssociatedCluster(Cluster *&pCluster) const;

    /**
     *  @brief  Get address of the mc particle associated with the track
     * 
     *  @param  pMCParticle to receive the address of the mc particle
     */
    StatusCode GetMCParticle(const MCParticle *&pMCParticle) const;

    /**
     *  @brief  Get the address of the parent track in the user framework
     *
     *  @param  the address of the parent track in the user framework
     */
    const void *GetParentTrackAddress() const;

    /**
     *  @brief  Get the parent track list
     * 
     *  @return the parent track list
     */
    const TrackList &GetParentTrackList() const;

    /**
     *  @brief  Get the sibling track list
     * 
     *  @return the sibling track list
     */
    const TrackList &GetSiblingTrackList() const;

    /**
     *  @brief  Get the daughter track list
     * 
     *  @return the daughter track list
     */
    const TrackList &GetDaughterTrackList() const;

private:
    /**
     *  @brief  Constructor
     * 
     *  @param  parameters the calo hit parameters
     */
    Track(const PandoraApi::TrackParameters &trackParameters);

    /**
     *  @brief  Destructor
     */
    ~Track();

    /**
     *  @brief  Set the mc particle associated with the track
     * 
     *  @param  pMCParticle the address of the mc particle
     */
    StatusCode SetMCParticle(MCParticle *const pMCParticle);

    /**
     *  @brief  Set the cluster associated with the track
     * 
     *  @param  pCluster the address of the associated cluster
     */
    StatusCode SetAssociatedCluster(Cluster *const pCluster);

    /**
     *  @brief  Remove the association with a cluster
     *
     *  @param  pCluster the address of the cluster with which the track is no longer associated
     */
    StatusCode RemoveAssociatedCluster(Cluster *const pCluster);

    /**
     *  @brief  Add a parent track to the parent track list
     * 
     *  @param  pTrack the address of the parent track
     */
    StatusCode AddParent(Track *const pTrack);

    /**
     *  @brief  Add a daughter track to the daughter track list
     * 
     *  @param  pTrack the address of the daughter track
     */
    StatusCode AddDaughter(Track *const pTrack);

    /**
     *  @brief  Add a sibling track to the sibling track list
     * 
     *  @param  pTrack the address of the sibling track
     */
    StatusCode AddSibling(Track *const pTrack);

    const float             m_d0;                       ///< The 2D impact parameter wrt (0,0), units mm
    const float             m_z0;                       ///< The z coordinate at the 2D distance of closest approach, units mm
    int                     m_chargeSign;               ///< The charge sign of the tracked particle
    const float             m_mass;                     ///< The mass of the tracked particle, units GeV

    const CartesianVector   m_momentumAtDca;            ///< The momentum vector at the 2D distance of closest approach, units GeV
    const float             m_momentumMagnitudeAtDca;   ///< The magnitude of the momentum at the 2D distance of closest approach, units GeV
    const float             m_energyAtDca;              ///< The track energy at the 2D distance of closest approach, units GeV

    const TrackState        m_trackStateAtStart;        ///< The track state at the start of the track, units mm and GeV
    const TrackState        m_trackStateAtEnd;          ///< The track state at the end of the track, units mm and GeV
    const TrackState        m_trackStateAtECal;         ///< The (sometimes projected) track state at the ecal

    const bool              m_reachesECal;              ///< Whether the track reaches the ecal
    TrackStateList          m_calorimeterProjections;   ///< A list of alternative track state projections to the calorimeters

    const Helix             *m_pHelixFitAtECal;         ///< Helix fit to the ecal track state

    Cluster                 *m_pAssociatedCluster;      ///< The address of an associated cluster
    const MCParticle        *m_pMCParticle;             ///< The address of the associated MC particle
    const void              *m_pParentAddress;          ///< The address of the parent track in the user framework

    TrackList               m_parentTrackList;          ///< The list of parent track addresses
    TrackList               m_siblingTrackList;         ///< The list of sibling track addresses
    TrackList               m_daughterTrackList;        ///< The list of daughter track addresses

    friend class PandoraContentApiImpl;
    friend class TrackManager;

    ADD_TEST_CLASS_FRIENDS;
};

/**
 *  @brief  Operator to dump track properties to an ostream
 *
 *  @param  stream the target ostream
 *  @param  track the track
 */
std::ostream &operator<<(std::ostream &stream, const Track &track);

/**
 *  @brief  Sort a track list by track momentum at the distance of closest approach
 *
 *  @param  trackList the track list to be sorted by momentum
 *  @param  momentumSortedTrackList to receive the momentum sorted track list
 */
StatusCode SortByMomentum(const TrackList &trackList, MomentumSortedTrackList &momentumSortedTrackList);

//------------------------------------------------------------------------------------------------------------------------------------------

inline bool Track::operator< (const Track &rhs) const
{
    return (!(m_momentumMagnitudeAtDca > rhs.m_momentumMagnitudeAtDca) && !(rhs.m_momentumMagnitudeAtDca > m_momentumMagnitudeAtDca) ?
        (this > &rhs) : (m_momentumMagnitudeAtDca > rhs.m_momentumMagnitudeAtDca));
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline bool Track::SortByEnergy(const Track *const pLhs, const Track *const pRhs)
{
    return (pLhs->GetEnergyAtDca() > pRhs->GetEnergyAtDca());
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline float Track::GetD0() const
{
    return m_d0;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline float Track::GetZ0() const
{
    return m_z0;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline int Track::GetChargeSign() const
{
    return m_chargeSign;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline float Track::GetMass() const
{
    return m_mass;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const CartesianVector &Track::GetMomentumAtDca() const
{
    return m_momentumAtDca;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline float Track::GetEnergyAtDca() const
{
    return m_energyAtDca;
}


//------------------------------------------------------------------------------------------------------------------------------------------

inline const TrackState &Track::GetTrackStateAtStart() const
{
    return m_trackStateAtStart;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const TrackState &Track::GetTrackStateAtEnd() const
{
    return m_trackStateAtEnd;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const TrackState &Track::GetTrackStateAtECal() const
{
    return m_trackStateAtECal;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline bool Track::ReachesECal() const
{
    return m_reachesECal;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const TrackStateList &Track::GetCalorimeterProjections() const
{
    return m_calorimeterProjections;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const Helix *const Track::GetHelixFitAtECal() const
{
    return m_pHelixFitAtECal;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline bool Track::HasAssociatedCluster() const
{
    return (NULL != m_pAssociatedCluster);
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline StatusCode Track::GetAssociatedCluster(Cluster *&pCluster) const
{
    if (NULL == m_pAssociatedCluster)
        return STATUS_CODE_NOT_INITIALIZED;

    pCluster = m_pAssociatedCluster;

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline StatusCode Track::GetMCParticle(const MCParticle *&pMCParticle) const
{
    if (NULL == m_pMCParticle)
        return STATUS_CODE_NOT_INITIALIZED;

    pMCParticle = m_pMCParticle;

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const void *Track::GetParentTrackAddress() const
{
    return m_pParentAddress;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const TrackList &Track::GetParentTrackList() const
{
    return m_parentTrackList;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const TrackList &Track::GetSiblingTrackList() const
{
    return m_siblingTrackList;
}

//------------------------------------------------------------------------------------------------------------------------------------------

inline const TrackList &Track::GetDaughterTrackList() const
{
    return m_daughterTrackList;
}

} // namespace pandora

#endif // #ifndef TRACK_H
