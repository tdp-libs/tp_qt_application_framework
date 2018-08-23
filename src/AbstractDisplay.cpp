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
QByteArray AbstractDisplay::saveState()const
{
  return QByteArray();
}

//##################################################################################################
void AbstractDisplay::loadState(const QByteArray& byteArray)
{
  TP_UNUSED(byteArray);
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
