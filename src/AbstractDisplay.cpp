#include "tdp_application_framework/AbstractDisplay.h"

#include <QDebug>

namespace tdp_application_framework
{
//int count =0;

//##################################################################################################
AbstractDisplay::AbstractDisplay(AbstractDisplayFactory* displayFactory, QWidget* parent):
  QWidget(parent),
  m_displayFactory(displayFactory)
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
