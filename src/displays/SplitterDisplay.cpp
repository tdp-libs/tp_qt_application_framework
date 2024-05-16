#include "tp_qt_application_framework/displays/SplitterDisplay.h"
#include "tp_qt_application_framework/AbstractDisplayFactory.h"
#include "tp_qt_application_framework/SplitWidget.h"

#include <QBoxLayout>
#include <QDebug>

namespace tp_qt_application_framework
{

//##################################################################################################
SplitterDisplay::SplitterDisplay(DisplayManager* displayManager, AbstractDisplayFactory* displayFactory, QWidget* parent):
  tp_qt_application_framework::AbstractDisplay(displayFactory, parent),
  m_splitWidget(new SplitWidget(displayManager))
{
  new QVBoxLayout(this);
  layout()->setContentsMargins(0, 0, 0, 0);
  layout()->addWidget(m_splitWidget);
}

//##################################################################################################
SplitterDisplay::~SplitterDisplay()=default;


//##################################################################################################
void SplitterDisplay::saveState(nlohmann::json& j) const
{
  m_splitWidget->saveState(j);
}

//##################################################################################################
void SplitterDisplay::loadState(const nlohmann::json& j)
{
  m_splitWidget->loadState(j);
}

//##################################################################################################
void SplitterDisplay::setToolBarsVisible(bool visible)
{
  AbstractDisplay::setToolBarsVisible(visible);
  m_splitWidget->setToolBarsVisible(visible);
}

//##################################################################################################
AbstractDisplayFactory* SplitterDisplay::makeDisplayFactory(DisplayManager* displayManager)
{
  return new DisplayFactory("Splitter", "Splitter", [=](auto displayFactory)
  {
    return new SplitterDisplay(displayManager, displayFactory);
  });
}

}
