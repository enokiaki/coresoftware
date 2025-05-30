// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef FUN4ALL_FUN4ALLOUTPUTMANAGER_H
#define FUN4ALL_FUN4ALLOUTPUTMANAGER_H

#include "Fun4AllBase.h"

#include <limits>
#include <string>
#include <vector>

class PHCompositeNode;

class Fun4AllOutputManager : public Fun4AllBase
{
 public:
  //! destructor
  ~Fun4AllOutputManager() override;

  //! print method (dump event selector)
  void Print(const std::string &what = "ALL") const override;

  //! add a node in outputmanager
  virtual int AddNode(const std::string & /*nodename*/)
  {
    return 0;
  }

  //! add a runwise node in outputmanager
  virtual int AddRunNode(const std::string & /*nodename*/)
  {
    return 0;
  }

  //! not write a node in outputmanager
  virtual int StripNode(const std::string & /*nodename*/)
  {
    return 0;
  }

  //! not write a runwise node in outputmanager
  virtual int StripRunNode(const std::string & /*nodename*/)
  {
    return 0;
  }

  virtual int StripCompositeNode(const std::string & /*nodename*/) {return 0;}

  virtual void SaveRunNode(const int) { return; }
  virtual void SaveDstNode(const int) { return; }

  /*! \brief
    add an event selector to the outputmanager.
    event will get written only if all event selectors process_event method
    return EVENT_OK
  */
  virtual int AddEventSelector(const std::string &recomodule);

  //! opens output file
  virtual int outfileopen(const std::string & /*nodename*/)
  {
    return 0;
  }

  //! Common method, called before calling virtual Write
  int WriteGeneric(PHCompositeNode *startNode);

  //! write starting from given node
  virtual int Write(PHCompositeNode * /*startNode*/)
  {
    return 0;
  }

  //! write specified node
  virtual int WriteNode(PHCompositeNode * /*thisNode*/)
  {
    return 0;
  }

  //! retrieves pointer to vector of event selector module names
  virtual std::vector<std::string> *EventSelector()
  {
    return &m_EventSelectorsVector;
  }

  //! retrieves pointer to vector of event selector module ids
  virtual std::vector<unsigned> *RecoModuleIndex()
  {
    return &m_RecoModuleIndexVector;
  }

  //! decides if event is to be written or not
  virtual int DoNotWriteEvent(std::vector<int> *retcodes) const;

  //! get number of Events
  virtual unsigned int EventsWritten() const { return m_NEvents; }
  //! increment number of events
  virtual void IncrementEvents(const unsigned int i) { m_NEvents += i; }
  //! set number of events
  virtual void SetEventsWritten(const unsigned int i) { m_NEvents = i; }
  //! get output file name
  virtual std::string OutFileName() const { return m_OutFileName; }
  //! set compression level (if implemented)
  virtual void CompressionSetting(const int /*i*/) { return; }

  void OutFileName(const std::string &name) { m_OutFileName = name; }
  void SetClosingScript(const std::string &script) { m_RunAfterClosingScript = script; }
  void SetClosingScriptArgs(const std::string &args) { m_ClosingArgs = args; }
  int RunAfterClosing();
  void UseFileRule() { m_UseFileRuleFlag = true; }
  bool ApplyFileRule() const { return m_UseFileRuleFlag; }
  void SetNEvents(const unsigned int nevt);
  unsigned int GetNEvents() const { return m_MaxEvents; }
  void FileRule(const std::string &newrule) { m_FileRule = newrule; }
  const std::string &FileRule() const { return m_FileRule; }
  void SplitLevel(const int split) { splitlevel = split; }
  void BufferSize(const int size) { buffersize = size; }
  int SplitLevel() const { return splitlevel; }
  int BufferSize() const { return buffersize; }
  int Segment() { return m_CurrentSegment; }

 protected:
  /*!
    constructor.
    is protected since we do not want the  class to be created in root macros
  */
  Fun4AllOutputManager(const std::string &myname);
  Fun4AllOutputManager(const std::string &myname, const std::string &outfname);

  //! current segment
  int m_CurrentSegment{0};

 private:
  //! add file rule to filename (runnumber-segment)
  bool m_UseFileRuleFlag{false};

  //! Buffer Size for baskets in root file
  int buffersize{std::numeric_limits<int>::min()};

  //! Split level of TBranches
  int splitlevel{std::numeric_limits<int>::min()};

  //! Number of Events
  unsigned int m_NEvents{0};

  //! Number of Events to write before roll over
  unsigned int m_MaxEvents{std::numeric_limits<unsigned int>::max()};

  //! Script to run after closing of file
  std::string m_RunAfterClosingScript;

  //! string with arguments for closing script
  std::string m_ClosingArgs;

  //! output file name
  std::string m_OutFileName;

  //! last output file name which was closed
  std::string m_LastClosedFileName;

  //! file rule when writing multiple segments (-<runnumber>-segment)
  std::string m_FileRule{"-%08d-%05d"};

  //! vector of event selectors modules
  std::vector<std::string> m_EventSelectorsVector;

  //! vector of associated module indexes
  std::vector<unsigned> m_RecoModuleIndexVector;
};

#endif
