// ROOT specific includes
//#include "TFile.h"
//#include "TTree.h"
//#include "TROOT.h"

// podio specific includes
#include "ASCIIReader.h"
#include "podio/CollectionIDTable.h"
#include "podio/CollectionBase.h"

#include "EventInfoCollection.h"
#include "ExampleWithArraymeCollection.h"
#include "ExampleWithStructCollection.h"


namespace podio {

  void ASCIIReader::readCollectionIDTable(){
    m_table = new CollectionIDTable();
   // auto metadatatree = static_cast<TTree*>(m_file->Get("metadata"));
    //metadatatree->SetBranchAddress("CollectionIDs",&m_table);
    //metadatatree->GetEntry(0);
  }

  CollectionBase* ASCIIReader::readCollection(const std::string& name) {
    // has the collection already been constructed?
    auto p = std::find_if(begin(m_inputs), end(m_inputs),
        [name](ASCIIReader::Input t){ return t.second == name;});
    if (p != end(m_inputs)){
      return p->first;
    }
    // get the branches in the ROOT file
    //auto branch = m_eventTree->GetBranch(name.c_str());
    //if (branch == nullptr) return nullptr;

    // look for involved classes
    /*TClass* theClass(nullptr);
    TClass* collectionClass(nullptr);
    auto result = f.find(name);
    if (result != m_storedClasses.end()) {
      theClass = result->second.first;
      collectionClass = result->second.second;
    } else {
      auto dataClassName = branch->GetClassName();
      theClass = gROOT->GetClass(dataClassName);
      if (theClass == nullptr) return nullptr;
      // now create the transient collections
      // some workaround until gcc supports regex properly:
      auto dataClassString = std::string(dataClassName);
      auto start = dataClassString.find("<");
      auto end   = dataClassString.find(">");
      //getting "TypeCollection" out of "vector<TypeData>"
      auto classname = dataClassString.substr(start+1, end-start-5);
      auto collectionClassName = classname+"Collection";
      collectionClass = gROOT->GetClass(collectionClassName.c_str());
      if (collectionClass == nullptr) return nullptr;
      // cache classes found for future usage
      m_storedClasses[name] = std::pair<TClass*,TClass*>(theClass, collectionClass);
    }
    // now create buffers and collections
    void* buffer = theClass->New();
    CollectionBase* collection = nullptr;
    collection = static_cast<CollectionBase*>(collectionClass->New());
    // connect buffer, collection and branch
    collection->setBuffer(buffer);
    branch->SetAddress(collection->getBufferAddress());
    m_inputs.emplace_back(std::make_pair(collection,name));
    branch->GetEntry(m_eventNumber);
    // load the collections containing references
    auto refCollections = collection->referenceCollections();
    if (refCollections != nullptr) {
      for (int i = 0, end = refCollections->size(); i!=end; ++i){
        branch = m_eventTree->GetBranch((name+"#"+std::to_string(i)).c_str());
        branch->SetAddress(&(*refCollections)[i]);
        branch->GetEntry(m_eventNumber);
      }
    }*/
    //std::cout<<4<<std::endl;
    if (name == "structs") {
        std::string line;
        //std::string line1;
        int id,xread,yread;
        //*m_file >> line1;
      //std::cout<< line1 <<std::endl;
      
      
        for (int i=0; i < 8*m_eventNumber+6; i++) {
            
             //std::cout<<5<<std::endl;
            getline (*m_file,line);
            
        }
        (*m_file) >> id >> xread >> yread;
        m_file->seekg(0);
        ExampleWithStructCollection* collection = new  ExampleWithStructCollection() ;
        //std::cout<<6<<std::endl;
        m_inputs.emplace_back(std::make_pair(collection,name));
        NotSoSimpleStruct b;
        b.data.x = xread;
        b.data.y = yread;
        auto structure = ExampleWithStruct(b);
        collection->push_back(structure);
        collection->setID(id);
        collection->prepareAfterRead();
        return collection;
    }
    //auto id = m_table->collectionID(name);
    
  }

    std::ifstream newFile;
  void ASCIIReader::openFile(const std::string& filename){
    /*m_file = TFile::Open(filename.c_str(),"READ","data file");
    if (m_file->IsZombie()) {
      exit(-1);
    }
    m_eventTree = static_cast<TTree*>( m_file->Get("events") );*/
    newFile.open( filename , std::ios::in );
    if ( !newFile ) {
      exit( -1 );
    }
      //std::string line1;
      //newFile >> line1;
      //std::cout<< line1 <<std::endl;
      m_file = &newFile;

    readCollectionIDTable();
  }

  void ASCIIReader::closeFile() {
    m_file->close();
  }

  void ASCIIReader::readEvent(){
    //m_eventTree->GetEntry();
    // first prepare all collections in memory...
    for(auto inputs : m_inputs){
      inputs.first->prepareAfterRead();
    }
    // ...then clean-up the references between them
//    for(auto inputs : m_inputs){
  //    inputs.first->setReferences(m_registry);

  //  }
  }
  bool ASCIIReader::isValid() const {
    //return m_file->IsOpen() && !m_file->IsZombie();
      if (m_file->is_open()) {
          return true;
      }
      return false;
  }

  ASCIIReader::~ASCIIReader() {
    // delete all collections
    // at the moment it is done in the EventStore;
    // TODO: who deletes the buffers?
  }

  void ASCIIReader::endOfEvent() {
    ++m_eventNumber;
    m_inputs.clear();
  }

  unsigned ASCIIReader::getEntries() const {
    //return m_eventTree->GetEntries();
      return 200;
  }

  void ASCIIReader::goToEvent(unsigned eventNumber) {
    m_eventNumber = eventNumber;
    m_inputs.clear();
  }


} //namespace
