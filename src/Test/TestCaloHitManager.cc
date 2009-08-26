/**
 *	@file	PandoraPFANew/src/Test/TestCaloHitManager.cc
 * 
 * 	@brief	Implementation of the tester for the mc manager class.
 * 
 *	$Log: $
 */

#include <assert.h>
#include <iostream>

#include "Test/TestCaloHitManager.h"
#include "Managers/CaloHitManager.h"
#include "Managers/MCManager.h"


namespace pandora
{



//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode TestCaloHitManager::Test_CreateCaloHit()
{
        std::cout << "--- --- CreateCaloHit | START ------------------------------" << std::endl;
   
        std::cout << "        create CaloHitManager" << std::endl;
        CaloHitManager* pCaloHitManager = new CaloHitManager();
	assert( pCaloHitManager != 0 ); // problem at creating a CaloHitManager

        std::cout << "        create CaloHitParameters" << std::endl;
	PandoraApi::CaloHitParameters caloHitParameters;
	caloHitParameters.m_energy = 10;
	caloHitParameters.m_pParentAddress = (void*)100;
	
        std::cout << "        create CaloHit with parameters" << std::endl;
 	assert( pCaloHitManager->CreateCaloHit( caloHitParameters ) == STATUS_CODE_SUCCESS ); 

        std::cout << "        get the created CaloHit" << std::endl;
//	CaloHit* caloHit = pCaloHitManager->GetCaloHit( (void*)100 ); 
//	assert( caloHit != 0 ); // CaloHit has not been created
//	assert( caloHit->GetUid() == (void*)100 ); // check if the Uid of the created CaloHit coincides with the one asked for
	

        std::cout << "        delete CaloHitManager" << std::endl;
	delete pCaloHitManager;
        std::cout << "--- --- CreateCaloHit | END ------------------------------" << std::endl;
	return STATUS_CODE_SUCCESS;
}



//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode TestCaloHitManager::Test_MatchCaloHitsToMCPfoTargets()
{
        std::cout << "--- --- MatchCaloHitsToMCPfoTargets | START ------------------------------" << std::endl;
   



        std::cout << "            first: make MC relationships and MCParticles" << std::endl;
        std::cout << "            create MCManager" << std::endl;
        MCManager* pMcManager = new MCManager();
	assert( pMcManager != 0 ); // problem at creating a MCManager

        std::cout << "            get MCParticle" << std::endl;
	MCParticle* root0Particle = NULL;
	pMcManager->RetrieveExistingOrCreateEmptyMCParticle( (void*)100, root0Particle ); 
	assert( root0Particle != 0 ); // MCParticle could not be created
	
        std::cout << "            get MCParticle" << std::endl;
	MCParticle* root1Particle = NULL;
	pMcManager->RetrieveExistingOrCreateEmptyMCParticle( (void*)101, root1Particle ); 
	assert( root1Particle != 0 ); // MCParticle could not be created

        std::cout << "            build a MCParticle-tree by adding relationships" << std::endl;
	/*
	 *  
	 * 100 
	 *  |--200 <=== will be the Pfo-target
	 *  |   |--300
	 *  |   |--301 ...............
	 *  |       |--400           |
	 *  |       |--401           |
	 *  |                        |
	 *  |--201                   |
	 *                           |
	 * 101                       |
	 *  |--210 ...................
	 *  |   |--310
	 *  |   |--311
	 *  |
	 *  |--211
	 *
	 *  102 <== isolated particle
	 *
	 */
        std::cout << "            create relationships" << std::endl;
	MCParticle *isolatedParticle = NULL;
	pMcManager->RetrieveExistingOrCreateEmptyMCParticle( (void*)102, isolatedParticle );

	assert( pMcManager->SetMCParentDaughterRelationship( (void*)100, (void*)200 ) == STATUS_CODE_SUCCESS );
	assert( pMcManager->SetMCParentDaughterRelationship( (void*)100, (void*)201 ) == STATUS_CODE_SUCCESS );

	assert( pMcManager->SetMCParentDaughterRelationship( (void*)101, (void*)210 ) == STATUS_CODE_SUCCESS );
	assert( pMcManager->SetMCParentDaughterRelationship( (void*)101, (void*)211 ) == STATUS_CODE_SUCCESS );

	assert( pMcManager->SetMCParentDaughterRelationship( (void*)200, (void*)300 ) == STATUS_CODE_SUCCESS );
	assert( pMcManager->SetMCParentDaughterRelationship( (void*)200, (void*)301 ) == STATUS_CODE_SUCCESS );

	assert( pMcManager->SetMCParentDaughterRelationship( (void*)301, (void*)400 ) == STATUS_CODE_SUCCESS );
	assert( pMcManager->SetMCParentDaughterRelationship( (void*)301, (void*)401 ) == STATUS_CODE_SUCCESS );

	assert( pMcManager->SetMCParentDaughterRelationship( (void*)210, (void*)310 ) == STATUS_CODE_SUCCESS );
	assert( pMcManager->SetMCParentDaughterRelationship( (void*)210, (void*)311 ) == STATUS_CODE_SUCCESS );

        std::cout << "            create cross-parental relationship" << std::endl;
	assert( pMcManager->SetMCParentDaughterRelationship( (void*)210, (void*)301 ) == STATUS_CODE_SUCCESS );

        std::cout << "            get one MCParticle which will be the PfoTarget" << std::endl;
	MCParticle* pfoTarget = NULL;
	pMcManager->RetrieveExistingOrCreateEmptyMCParticle( (void*)200, pfoTarget );

        std::cout << "            set the PfoTarget in the whole MCParticle tree" << std::endl;
	pfoTarget->SetPfoTargetInTree( pfoTarget );

        std::cout << "            check all MCParticles in the tree if their pfo-target is set correctly" << std::endl;
	MCParticle *mcP = NULL;
	MCParticle *pfo = NULL;
	pMcManager->RetrieveExistingOrCreateEmptyMCParticle( (void*)100, mcP );
	pfo = NULL;
	assert( mcP->GetPfoTarget(pfo) == STATUS_CODE_SUCCESS );
	pMcManager->RetrieveExistingOrCreateEmptyMCParticle( (void*)200, mcP );
	pMcManager->RetrieveExistingOrCreateEmptyMCParticle( (void*)300, mcP );
	pMcManager->RetrieveExistingOrCreateEmptyMCParticle( (void*)301, mcP );
	pMcManager->RetrieveExistingOrCreateEmptyMCParticle( (void*)400, mcP );
	pMcManager->RetrieveExistingOrCreateEmptyMCParticle( (void*)401, mcP );
	pMcManager->RetrieveExistingOrCreateEmptyMCParticle( (void*)210, mcP );
	pMcManager->RetrieveExistingOrCreateEmptyMCParticle( (void*)101, mcP );
	pMcManager->RetrieveExistingOrCreateEmptyMCParticle( (void*)211, mcP );
	pMcManager->RetrieveExistingOrCreateEmptyMCParticle( (void*)310, mcP );
	pMcManager->RetrieveExistingOrCreateEmptyMCParticle( (void*)311, mcP );

	MCParticle* isolated = NULL;
	pMcManager->RetrieveExistingOrCreateEmptyMCParticle( (void*)102, isolated );







        std::cout << "            now the real testing for the CaloHitManager" << std::endl;
        std::cout << "            create the CaloHitManager" << std::endl;
        CaloHitManager* pCaloHitManager = new CaloHitManager();
	assert( pCaloHitManager != 0 ); // problem at creating a CaloHitManager

	
        std::cout << "            create the CaloHits" << std::endl;
//	pCaloHitManager->CreateCaloHit( 

        std::cout << "        create CaloHitParameters" << std::endl;
	PandoraApi::CaloHitParameters caloHitParameters;
	caloHitParameters.m_energy = 10;
	caloHitParameters.m_pParentAddress = (void*)9000;
	
        std::cout << "        create CaloHit with parameters" << std::endl;
 	assert( pCaloHitManager->CreateCaloHit( caloHitParameters ) == STATUS_CODE_SUCCESS ); 


	caloHitParameters.m_energy = 11;
	caloHitParameters.m_pParentAddress = (void*)9001;
 	assert( pCaloHitManager->CreateCaloHit( caloHitParameters ) == STATUS_CODE_SUCCESS ); 

	caloHitParameters.m_energy = 12;
	caloHitParameters.m_pParentAddress = (void*)9002;
 	assert( pCaloHitManager->CreateCaloHit( caloHitParameters ) == STATUS_CODE_SUCCESS ); 

	caloHitParameters.m_energy = 13;
	caloHitParameters.m_pParentAddress = (void*)9003;
 	assert( pCaloHitManager->CreateCaloHit( caloHitParameters ) == STATUS_CODE_SUCCESS ); 

	caloHitParameters.m_energy = 14;
	caloHitParameters.m_pParentAddress = (void*)9004;
 	assert( pCaloHitManager->CreateCaloHit( caloHitParameters ) == STATUS_CODE_SUCCESS ); 


	
	pMcManager->SetCaloHitToMCParticleRelationship( (void*)9001, (void*)301, 1.0 );
	pMcManager->SetCaloHitToMCParticleRelationship( (void*)9002, (void*)102, 1.0 );
	pMcManager->SetCaloHitToMCParticleRelationship( (void*)9003, (void*)400, 1.0 );
	pMcManager->SetCaloHitToMCParticleRelationship( (void*)9004, (void*)401, 1.0 );


	pMcManager->SelectPfoTargets();

	UidToMCParticleMap caloHitToPfoTargetMap;
	pMcManager->CreateCaloHitToPfoTargetMap(caloHitToPfoTargetMap);

	assert( !caloHitToPfoTargetMap.empty() );
//	assert( caloHitToPfoTargetMap.size() == );

	pCaloHitManager->MatchCaloHitsToMCPfoTargets(caloHitToPfoTargetMap);
	
	for ( UidToMCParticleMap::iterator it = caloHitToPfoTargetMap.begin(), itEnd = caloHitToPfoTargetMap.end(); it != itEnd; it++ )
	{
	   MCParticle* mcP = NULL;
	   Uid mcUid = it->second->m_uid;

	   // uhh .. ugly
	   UidToMCParticleMap::iterator itMcParticle = pMcManager->m_uidToMCParticleMap.find(mcUid);
	   
	   mcP = itMcParticle->second;

	   MCParticle* pfo = NULL;
	   mcP->GetPfoTarget(pfo);
	   assert( mcP == pfo );

	   if( !(mcP == isolated) )
	   {
	      std::cout << "            tree particle found mcP " << mcP << "  pfoTarget " << pfoTarget<< std::endl;
	      assert( mcP == pfoTarget );
	      assert( pfo == pfoTarget );
	      assert( pfo != isolated );
	   }
	   else
	   {
	      std::cout << "            isolated particle found mcP " << mcP << "  pfoTarget " << pfoTarget<< std::endl;
	      assert( mcP != pfoTarget );
	      assert( pfo == isolated );
	   }
	   
	}
	

        std::cout << "        delete CaloHitManager" << std::endl;
	delete pCaloHitManager;
        std::cout << "        delete MCManager" << std::endl;
	delete pMcManager;
        std::cout << "--- --- MatchCaloHitsToMCPfoTargets | END ------------------------------" << std::endl;
	return STATUS_CODE_SUCCESS;
}


//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode TestCaloHitManager::Test_GetCaloHitVector()
{
        std::cout << "--- --- GetCaloHitVector | START ------------------------------" << std::endl;
   
        std::cout << "        create CaloHitManager" << std::endl;
        CaloHitManager* pCaloHitManager = new CaloHitManager();
	assert( pCaloHitManager != 0 ); // problem at creating a CaloHitManager


        std::cout << "        delete CaloHitManager" << std::endl;
	delete pCaloHitManager;
        std::cout << "--- --- GetCaloHitVector | END ------------------------------" << std::endl;
	return STATUS_CODE_SUCCESS;
}


//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode TestCaloHitManager::Test_GetCurrentOrderedCaloHitVector()
{
        std::cout << "--- --- GetCurrentOrderedCaloHitVector | START ------------------------------" << std::endl;
   
        std::cout << "        create CaloHitManager" << std::endl;
        CaloHitManager* pCaloHitManager = new CaloHitManager();
	assert( pCaloHitManager != 0 ); // problem at creating a CaloHitManager


        std::cout << "        delete CaloHitManager" << std::endl;
	delete pCaloHitManager;
        std::cout << "--- --- GetCurrentOrderedCaloHitVector | END ------------------------------" << std::endl;
	return STATUS_CODE_SUCCESS;
}


//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode TestCaloHitManager::Test_Reset()
{
        std::cout << "--- --- Reset | START ------------------------------" << std::endl;
   
        std::cout << "        create CaloHitManager" << std::endl;
        CaloHitManager* pCaloHitManager = new CaloHitManager();
	assert( pCaloHitManager != 0 ); // problem at creating a CaloHitManager


        std::cout << "        delete CaloHitManager" << std::endl;
	delete pCaloHitManager;
        std::cout << "--- --- Reset | END ------------------------------" << std::endl;
	return STATUS_CODE_SUCCESS;
}



//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode TestCaloHitManager::Test_Combined()
{
        std::cout << "--- --- Combined | START ------------------------------" << std::endl;
   
        std::cout << "        create CaloHitManager" << std::endl;
        CaloHitManager* pCaloHitManager = new CaloHitManager();
	assert( pCaloHitManager != 0 ); // problem at creating a CaloHitManager
	

        std::cout << "        delete CaloHitManager" << std::endl;
	delete pCaloHitManager;

        std::cout << "--- --- Combined | END ------------------------------" << std::endl;
	return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode TestCaloHitManager::Test_All()
{
        std::cout << "--- --- ALL | START ------------------------------" << std::endl;
        assert( Test_CreateCaloHit() == STATUS_CODE_SUCCESS );
        assert( Test_MatchCaloHitsToMCPfoTargets() == STATUS_CODE_SUCCESS );
	assert( Test_Combined() == STATUS_CODE_SUCCESS );

        std::cout << "--- --- ALL | END ------------------------------" << std::endl;
	return STATUS_CODE_SUCCESS;
}



} // namespace pandora