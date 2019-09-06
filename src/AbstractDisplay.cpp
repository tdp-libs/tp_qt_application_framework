#include "tdp_application_framework/AbstractDisplay.h"

#include <QDebug>

namespace tdp_application_framework
{
//int count =0;

//##################################################################################################
AbstractDisplay::AbstractDisplay(AbstractDisplayFactory* displayFactory, QWidget* parent):
  QWidget(parent),
  m_displayFactory(displayFactory),
  m_toolBarsVisible(true)
{
}

//##################################################################################################
AbstractDisplayFactory* AbstractDisplay::displayFactory()const
{
  return m_displayFactory;
}

//##################################################################################################
nlohmann::json AbstractDisplay::saveState()const
{
  return nlohmann::json();
}

//##################################################################################################
void AbstractDisplay::loadState(const nlohmann::json& j)
{
  TP_UNUSED(j);
}

//##################################################################################################
void AbstractDisplay::setToolBarsVisible(bool visible)
{
  m_toolBarsVisible = visible;
}

//##################################################################################################
bool AbstractDisplay::toolBarsVisible()const
{
  return m_toolBarsVisible;
}

//##################################################################################################
QWidget* AbstractDisplay::configWidget()
{
  return nullptr;
}

//##################################################################################################
bool AbstractDisplay::readyToClose()const
{
  return true;
}

}
