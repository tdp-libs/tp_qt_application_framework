#include "tp_qt_application_framework/DisplayManager.h"
#include "tp_qt_application_framework/AbstractDisplayFactory.h"
#include "tp_qt_application_framework/AbstractDisplay.h"

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

  DisplayManager* q;

  QList<AbstractDisplayFactory*> displayFactories;
  QStringListModel* factoriesModel;

  //################################################################################################
  Private(DisplayManager* q_):
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
  qDeleteAll(d->displayFactories);
  delete d;
}

//##################################################################################################
void DisplayManager::addDisplayFactory(AbstractDisplayFactory* displayFactory)
{
  d->displayFactories.append(displayFactory);
  d->updateModel();
}

//##################################################################################################
const QList<AbstractDisplayFactory*>& DisplayManager::displayFactories()const
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
QAbstractItemModel* DisplayManager::factoriesModel()const
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
