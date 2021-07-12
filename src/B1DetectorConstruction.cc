#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  //add new material --caryn
  G4Material* matNi = nist->FindOrBuildMaterial("G4_Ni");
  G4Material* matCu = nist->FindOrBuildMaterial("G4_Cu");
  G4Material* matMo = nist->FindOrBuildMaterial("G4_Mo");

  G4Material* matinconel625 = new G4Material( "Inconel625",
  					      8.442 * g/cm3,
  					     3);
  //(0.305 lbs/in3)(453.592 g/lb)(in/2.54 cm)^3=8.442g/cm2
    matinconel625->AddMaterial(matNi,  70 * perCent);
    matinconel625->AddMaterial(matCu,  20 * perCent);
   matinconel625->AddMaterial(matMo,  10 * perCent);

    //  G4Material* matinconel625 = new G4Material(name = "Inconel625",
  //					     density = 1 * g/cm2,
  //					     ncomponents =3);
  //  matinconel625->AddMaterial(matNi, fractionmass = 70 * perCent);
  //  matinconel625->AddMaterial(matCu, fractionmass = 20 * perCent);
  //  matinconel625->AddMaterial(matMo, fractionmass = 10 * perCent);


  //


  G4double world_sizeXY = 2*cm;
  G4double world_sizeZ  = 20*cm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
  G4Material* tgtMat = nist->FindOrBuildMaterial("G4_VITON");
  //   G4Material* shieldMat = nist->FindOrBuildMaterial("G4_Al");
    G4Material* shieldMat = matinconel625;
  G4double shieldThickness = 1.25*cm;
  //  G4Material* shield2Mat = matinconel625;
     G4Material* shield2Mat = nist->FindOrBuildMaterial("G4_Al");
  G4double shield2Thickness = 2.5*cm;



  //G4_STAINLESS-STEEL
  // G4Material* tgtMat = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
  // G4Material* shieldMat = nist->FindOrBuildMaterial("G4_Pb");
  //G4double shieldThickness = 5*cm;
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
	      0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
  
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  G4Box* solidSh =    
    new G4Box("solidSh",                    //its name
	      0.5*2*cm, 0.5*2*cm, 0.5*shieldThickness); //its size

  G4Box* solidSh2 =    
    new G4Box("solidSh2",                    //its name
	      0.5*2*cm, 0.5*2*cm, 0.5*shield2Thickness); //its size

                     
  G4Box* solidFB =    
    new G4Box("solidFB",                    //its name
	      0.5*2*cm, 0.5*2*cm, 0.5*1*mm); //its size
  G4Box* solidMid =    
    new G4Box("solidFB",                    //its name
	      0.5*2*cm, 0.5*2*cm, 0.5*1*mm); //its size

  G4LogicalVolume* logicSh =                         
    new G4LogicalVolume(solidSh,            //its solid
                        shieldMat,             //its material
                        "logicSh");         //its name

  G4LogicalVolume* logicSh2 =                         
    new G4LogicalVolume(solidSh2,            //its solid
                        shield2Mat,             //its material
                        "logicSh2");         //its name


  G4LogicalVolume* logicF =                         
    new G4LogicalVolume(solidFB,            //its solid
                        tgtMat,             //its material
                        "logicF");         //its name
  G4LogicalVolume* logicB =                         
    new G4LogicalVolume(solidFB,            //its solid
                        tgtMat,             //its material
                        "logicB");         //its name
  G4LogicalVolume* logicMid =
    new G4LogicalVolume(solidMid,            //its solid
                        tgtMat,             //its material
                        "logicMid");         //its name

  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,-4*cm),
                    logicSh,                //its logical volume
                    "shield",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,2*cm),
                    logicSh2,                //its logical volume
                    "shield2",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

 
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,-1.1*mm),
                    logicF,                //its logical volume
                    "front",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,1.1*mm),
                    logicB,                //its logical volume
                    "back",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),
                    logicMid,                //its logical volume
                    "mid",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 
                
  // Set Shape2 as scoring volume
  //
  fScoringVolume.push_back(logicF);
  fScoringVolume.push_back(logicMid);
  fScoringVolume.push_back(logicB);

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
