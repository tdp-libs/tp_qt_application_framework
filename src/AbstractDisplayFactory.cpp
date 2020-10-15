#include "tp_qt_application_framework/AbstractDisplayFactory.h"

namespace tp_qt_application_framework
{

//##################################################################################################
AbstractDisplayFactory::AbstractDisplayFactory(QString title, QString id):
  m_title(std::move(title)),
  m_id(std::move(id))
{

}

//##################################################################################################
AbstractDisplayFactory::~AbstractDisplayFactory()=default;

//##################################################################################################
QString AbstractDisplayFactory::title() const
{
  return m_title;
}

//##################################################################################################
QString AbstractDisplayFactory::id() const
{
  return m_id;
}

}
