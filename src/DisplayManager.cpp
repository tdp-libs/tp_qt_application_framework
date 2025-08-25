#include "tp_qt_application_framework/DisplayManager.h"
#include "tp_qt_application_framework/AbstractDisplayFactory.h"
#include "tp_qt_application_framework/AbstractDisplay.h"

#include "tp_utils/RefCount.h"
#include "tp_utils/TimeUtils.h"

#include <QAbstractItemModel>
#include <QList>
#include <QStringListModel>

namespace tp_qt_application_framework
{

//##################################################################################################
struct DisplayManager::Private
{
  TP_REF_COUNT_OBJECTS("tp_qt_application_framework::DisplayManager::Private");
  TP_NONCOPYABLE(Private);

  Q* q;

  QList<AbstractDisplayFactory*> displayFactories;
  QStringListModel* factoriesModel;

  enum class SortDisplays
  {
    OrderAdded,
    Title
  };

  SortDisplays sortDisplays{SortDisplays::Title};

  //################################################################################################
  Private(Q* q_):
    q(q_),
    factoriesModel(new QStringListModel(q))
  {

  }

  //################################################################################################
  void updateModel()
  {
    QStringList factories;

    factories.append("Blank");

    Q_FOREACH(AbstractDisplayFactory* factory, displayFactories)
      factories.append(factory->title());

    factoriesModel->setStringList(factories);
  }
};

//##################################################################################################
DisplayManager::DisplayManager(QObject* parent):
  QObject(parent),
  d(new Private(this))
{

}

//##################################################################################################
DisplayManager::~DisplayManager()
{
  TP_FUNCTION_TIME("DisplayManager::~DisplayManager");
  qDeleteAll(d->displayFactories);
  delete d;
}

//##################################################################################################
void DisplayManager::addDisplayFactory(AbstractDisplayFactory* displayFactory)
{
  switch(d->sortDisplays)
  {
    case Private::SortDisplays::OrderAdded:
    {
      d->displayFactories.append(displayFactory);
      break;
    }

    case Private::SortDisplays::Title:
    {
      int i=0;
      for(; i<d->displayFactories.size(); i++)
        if(d->displayFactories.at(i)->title()>displayFactory->title())
          break;


      d->displayFactories.insert(i, displayFactory);
      break;
    }
  }

  d->updateModel();
}

//##################################################################################################
const QList<AbstractDisplayFactory*>& DisplayManager::displayFactories() const
{
  return d->displayFactories;
}

//##################################################################################################
AbstractDisplay* DisplayManager::produceDisplay(int index)
{
  index--;

  if(index>=0 && index<d->displayFactories.size())
    return d->displayFactories.at(index)->produceDisplay();

  return nullptr;
}

//##################################################################################################
QAbstractItemModel* DisplayManager::factoriesModel() const
{
  return d->factoriesModel;
}

//##################################################################################################
int DisplayManager::factoryIndex(const QString& factoryID)
{
  int fMax = d->displayFactories.size();
  for(int f=0; f<fMax; f++)
    if(d->displayFactories.at(f)->id() == factoryID)
      return f+1;

  return -1;
}

}
