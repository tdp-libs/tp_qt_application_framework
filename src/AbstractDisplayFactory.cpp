#include "tdp_application_framework/AbstractDisplayFactory.h"

namespace tdp_application_framework
{

//##################################################################################################
AbstractDisplayFactory::AbstractDisplayFactory(const QString& title, const QString& id):
  m_title(title),
  m_id(id)
{

}

//##################################################################################################
AbstractDisplayFactory::~AbstractDisplayFactory()=default;

//##################################################################################################
QString AbstractDisplayFactory::title()const
{
  return m_title;
}

//##################################################################################################
QString AbstractDisplayFactory::id()const
{
  return m_id;
}

}
