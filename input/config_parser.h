/*
 * config_parser.h
 *
 *  Created on: Oct 4, 2024
 *      Author: gizbo89
 */
#ifndef XML_PARSER_HPP
#define XML_PARSER_HPP
/**
 *  @file
 *  Class "GetConfig" provides the functions to read the XML data.
 *  @version 1.0
 */
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

#include <string>
#include <stdexcept>

// Error codes

enum {
   ERROR_ARGS = 1,
   ERROR_XERCES_INIT,
   ERROR_PARSE,
   ERROR_EMPTY_DOCUMENT
};

class GetConfig
{
public:
   GetConfig();
  ~GetConfig();
   char * search(const std::string& TAG, const std::string& ATTRIBUTE) noexcept(false);
   void init(std::string& configFile) noexcept(false);

private:
   xercesc::XercesDOMParser *m_ConfigFileParser;
};
#endif
