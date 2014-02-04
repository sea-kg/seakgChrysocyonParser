
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * autoxmlclass © 2013 sea-kg (mrseakg@gmail.com)          *
 * source code of autoxmlclass:                            *
 *        https://github.com/sea-kg/autoxmlclass/          *
 *                                                         * 
 * Attention:                                              *
 *  It's code was generated on server:                     *
 *        http://localhost/xmlclass/index.php
 *  and please NOT CHANGING this code!!!                   *
 *                                                         *  
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef _seakgXMLInterface_h
#define _seakgXMLInterface_h

#include <QFile>
#include <QStack>
#include <QList>
#include <QString>
#include <QStringList>
#include <QXmlStreamReader>
#include <QTextStream>

namespace seakgXMLInterface {

	class _class_text;
	class _class_comment;
	class _method;
	class _methods;
	class _last_date_updated;
	class _uuid;
	class _source_filepath;
	class _project_name;
	class _class;

	class _specXMLElement {
		public:
			virtual QString nameOfElement() { return ""; };
			virtual bool hasBody() { return false; };
			virtual bool setBody(QString /*body*/) { return false; };
			virtual bool setAttribute(QString /*name*/, QString /*value*/) { return false; };
			virtual bool addChildElement(QString /*name*/, _specXMLElement * /*pElem*/) { return false; };
	};
	
	//-------------------------------

	class _class_text : public _specXMLElement {
		public:

			// _specXMLElement
			virtual QString nameOfElement();
			virtual bool hasBody();
			virtual bool setBody(QString body);
			virtual bool setAttribute(QString name, QString value);
			virtual bool addChildElement(QString name, _specXMLElement *);

			QString Body;

	};

	//-------------------------------
	
	class _class_comment : public _specXMLElement {
		public:

			// _specXMLElement
			virtual QString nameOfElement();
			virtual bool hasBody();
			virtual bool setBody(QString body);
			virtual bool setAttribute(QString name, QString value);
			virtual bool addChildElement(QString name, _specXMLElement *);

			QString Body;

	};

	//-------------------------------
	
	class _method : public _specXMLElement {
		public:

			// _specXMLElement
			virtual QString nameOfElement();
			virtual bool hasBody();
			virtual bool setBody(QString body);
			virtual bool setAttribute(QString name, QString value);
			virtual bool addChildElement(QString name, _specXMLElement *);

			// attributes 
			QString name;

			// elements
			QString Body;

	};

	//-------------------------------
	
	class _methods : public _specXMLElement {
		public:

			// _specXMLElement
			virtual QString nameOfElement();
			virtual bool hasBody();
			virtual bool setBody(QString body);
			virtual bool setAttribute(QString name, QString value);
			virtual bool addChildElement(QString name, _specXMLElement *);

			QList<_method *> methods;
	};

	//-------------------------------
	
	class _last_date_updated : public _specXMLElement {
		public:

			// _specXMLElement
			virtual QString nameOfElement();
			virtual bool hasBody();
			virtual bool setBody(QString body);
			virtual bool setAttribute(QString name, QString value);
			virtual bool addChildElement(QString name, _specXMLElement *);

			QString Body;

	};

	//-------------------------------
	
	class _uuid : public _specXMLElement {
		public:

			// _specXMLElement
			virtual QString nameOfElement();
			virtual bool hasBody();
			virtual bool setBody(QString body);
			virtual bool setAttribute(QString name, QString value);
			virtual bool addChildElement(QString name, _specXMLElement *);

			QString Body;

	};

	//-------------------------------
	
	class _source_filepath : public _specXMLElement {
		public:

			// _specXMLElement
			virtual QString nameOfElement();
			virtual bool hasBody();
			virtual bool setBody(QString body);
			virtual bool setAttribute(QString name, QString value);
			virtual bool addChildElement(QString name, _specXMLElement *);

			QString Body;

	};

	//-------------------------------
	
	class _project_name : public _specXMLElement {
		public:

			// _specXMLElement
			virtual QString nameOfElement();
			virtual bool hasBody();
			virtual bool setBody(QString body);
			virtual bool setAttribute(QString name, QString value);
			virtual bool addChildElement(QString name, _specXMLElement *);

			QString Body;

	};

	//-------------------------------
	
	class _class : public _specXMLElement {
		public:

			// _specXMLElement
			virtual QString nameOfElement();
			virtual bool hasBody();
			virtual bool setBody(QString body);
			virtual bool setAttribute(QString name, QString value);
			virtual bool addChildElement(QString name, _specXMLElement *);

			// attributes 
			QString id;
			QString name;
			QString version_format;

			// elements
			_project_name * project_name; 
			_source_filepath * source_filepath; 
			_uuid * uuid; 
			_last_date_updated * last_date_updated; 
			_methods * methods; 
			_class_comment * class_comment; 
			_class_text * class_text; 
	};

	//-------------------------------
	 
	_specXMLElement * createElement(QString strName);

	_class * readFromXML(QString fileXml);
	
} // namespace seakgXMLInterface

#endif // _seakgXMLInterface_h
