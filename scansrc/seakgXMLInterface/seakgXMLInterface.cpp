
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

#include "seakgXMLInterface.h"

namespace seakgXMLInterface {
	

	//-------------------------------

	QString _class_text::nameOfElement() {
		return "class_text";
	};

	//-------------------------------

	bool _class_text::hasBody() {
		return true;
	};

	//-------------------------------

	bool _class_text::setBody(QString body) {
		Body = body;
		return true;
	};

	//-------------------------------

	bool _class_text::setAttribute(QString /*name*/, QString /*value*/) {
		return false;
	};
	
	//-------------------------------

	bool _class_text::addChildElement(QString /*strName*/, _specXMLElement */*pElem*/) {
		return false;
	};
		
	//-------------------------------


	//-------------------------------

	QString _class_comment::nameOfElement() {
		return "class_comment";
	};

	//-------------------------------

	bool _class_comment::hasBody() {
		return true;
	};

	//-------------------------------

	bool _class_comment::setBody(QString body) {
		Body = body;
		return true;
	};

	//-------------------------------

	bool _class_comment::setAttribute(QString /*name*/, QString /*value*/) {
		return false;
	};
	
	//-------------------------------

	bool _class_comment::addChildElement(QString /*strName*/, _specXMLElement */*pElem*/) {
		return false;
	};
		

	//-------------------------------

	QString _method::nameOfElement() {
		return "method";
	};

	//-------------------------------

	bool _method::hasBody() {
		return true;
	};

	//-------------------------------

	bool _method::setBody(QString body) {
		Body = body;
		return true;
	};

	//-------------------------------

	bool _method::setAttribute(QString name, QString value) {
		if(name == "name")
			name = value;
		else
			return false;
		return true;
	}

	//-------------------------------

	bool _method::addChildElement(QString /*strName*/, _specXMLElement */*pElem*/) {
		return false;
	};
		
	//-------------------------------


	//-------------------------------

	QString _methods::nameOfElement() {
		return "methods";
	};

	//-------------------------------

	bool _methods::hasBody() {
		return false;
	};

	//-------------------------------

	bool _methods::setBody(QString /*body*/) {
		 return false;
	};

	//-------------------------------

	bool _methods::setAttribute(QString /*name*/, QString /*value*/) {
		return false;
	};

	//-------------------------------

	bool _methods::addChildElement(QString strName, _specXMLElement *pElem) {
		if(strName == "method") {
			_methods *p = dynamic_cast<_method *>(pElem);
			if(p == NULL) return false;
			methods << p;
		}
		else
			return false;
		return true;
	};

		
	//-------------------------------


	//-------------------------------

	QString _last_date_updated::nameOfElement() {
		return "last_date_updated";
	};

	//-------------------------------

	bool _last_date_updated::hasBody() {
		return true;
	};

	//-------------------------------

	bool _last_date_updated::setBody(QString body) {
		Body = body;
		return true;
	};

	//-------------------------------

	bool _last_date_updated::setAttribute(QString /*name*/, QString /*value*/) {
	return false;
};
	
	}

	//-------------------------------

	bool _last_date_updated::addChildElement(QString /*strName*/, _specXMLElement */*pElem*/) {
		return false;
	};
		
	//-------------------------------


	//-------------------------------

	QString _uuid::nameOfElement() {
		return "uuid";
	};

	//-------------------------------

	bool _uuid::hasBody() {
		return true;
	};

	//-------------------------------

	bool _uuid::setBody(QString body) {
		Body = body;
		return true;
	};

	//-------------------------------

	bool _uuid::setAttribute(QString /*name*/, QString /*value*/) {
		return false;
	};

	//-------------------------------

	bool _uuid::addChildElement(QString /*strName*/, _specXMLElement */*pElem*/) {
		return false;
	};
		
	//-------------------------------


	//-------------------------------

	QString _source_filepath::nameOfElement() {
		return "source_filepath";
	};

	//-------------------------------

	bool _source_filepath::hasBody() {
		return true;
	};

	//-------------------------------

	bool _source_filepath::setBody(QString body) {
		Body = body;
		return true;
	};

	//-------------------------------

	bool _source_filepath::setAttribute(QString /*name*/, QString /*value*/) {
		return false;
	};
	
	//-------------------------------

	bool _source_filepath::addChildElement(QString /*strName*/, _specXMLElement */*pElem*/) {
		return false;
	};
		
	//-------------------------------


	//-------------------------------

	QString _project_name::nameOfElement() {
		return "project_name";
	};

	//-------------------------------

	bool _project_name::hasBody() {
		return true;
	};

	//-------------------------------

	bool _project_name::setBody(QString body) {
		Body = body;
		return true;
	};

	//-------------------------------

	bool _project_name::setAttribute(QString /*name*/, QString /*value*/) {
		return false;
	};

	//-------------------------------

	bool _project_name::addChildElement(QString /*strName*/, _specXMLElement */*pElem*/) {
		return false;
	};
		
	//-------------------------------


	//-------------------------------

	QString _class::nameOfElement() {
		return "class";
	};

	//-------------------------------

	bool _class::hasBody() {
		return false;
	};

	//-------------------------------

	bool _class::setBody(QString /*body*/) {
		 return false;
	};

	//-------------------------------

	bool _class::setAttribute(QString name, QString value) {
		if(name == "id")
			id = value;
		else if(name == "name")
			name = value;
		else if(name == "version_format")
			version_format = value;
		else
			return false;
		return true;
	}

	//-------------------------------

	bool _class::addChildElement(QString strName, _specXMLElement *pElem) {
		if(strName == "project_name") {
			project_name = dynamic_cast<_project_name *>(pElem);
		}
		else if(strName == "source_filepath") {
			source_filepath = dynamic_cast<_source_filepath *>(pElem);
		}
		else if(strName == "uuid") {
			uuid = dynamic_cast<_uuid *>(pElem);
		}
		else if(strName == "last_date_updated") {
			last_date_updated = dynamic_cast<_last_date_updated *>(pElem);
		}
		else if(strName == "methods") {
			methods = dynamic_cast<_methods *>(pElem);
		}
		else if(strName == "class_comment") {
			class_comment = dynamic_cast<_class_comment *>(pElem);
		}
		else if(strName == "class_text") {
			class_text = dynamic_cast<_class_text *>(pElem);
		}
		else
			return false;
		return true;
	};

		
	//-------------------------------
 
	_specXMLElement * createElement(QString strName) {
		_specXMLElement *elem = NULL;	

		if(strName == "class_text") elem = new _class_text();
		if(strName == "class_comment") elem = new _class_comment();
		if(strName == "method") elem = new _method();
		if(strName == "methods") elem = new _methods();
		if(strName == "last_date_updated") elem = new _last_date_updated();
		if(strName == "uuid") elem = new _uuid();
		if(strName == "source_filepath") elem = new _source_filepath();
		if(strName == "project_name") elem = new _project_name();
		if(strName == "class") elem = new _class();
		return elem;
	};
	
	//-------------------------------

	
	_class * readFromXML(QString fileXml) {
		_class *root = NULL;

		// init xml stream
		QFile file(fileXml);
		QXmlStreamReader xmlReader;
	
		//QString line;
		if ( !file.open(QIODevice::ReadOnly) )
			return false;
	
		{
			QTextStream t( &file );
			// stream.setCodec("CP-866");
			xmlReader.addData(t.readAll());
		}	
	
		// start reading
		QStack<_specXMLElement *> stackElements;
		while(!xmlReader.atEnd()) 
		{
			if(xmlReader.isCharacters() && stackElements.count() != 0)
			{
				_specXMLElement *pElemTop = stackElements.top();
				if(pElemTop->hasBody())
				  pElemTop->setBody(xmlReader.readElementText());
			}
		
			if(xmlReader.isStartElement())
			{ 
				QString strName = xmlReader.name().toString();
				_specXMLElement *elem = createElement(strName);
			
				_specXMLElement *parentElem = (stackElements.count() != 0) ? stackElements.top() : NULL;

				if(stackElements.count() == 0)
					root = (_class *)elem;
								
				if(parentElem != NULL)
					parentElem->addChildElement(strName,elem);

				stackElements.push(elem);
			
				for(int i = 0;  i < xmlReader.attributes().count(); i++)
				{
					QXmlStreamAttribute attr = xmlReader.attributes().at(i);
					elem->setAttribute(attr.name().toString(), attr.value().toString());
				}
			}
		
			if(xmlReader.isEndElement())
			{
				stackElements.pop();
			}
			xmlReader.readNext();		

		};
	
		if(xmlReader.hasError())
		{
			return NULL;
			// std::cout << xmlReader.errorString().toStdString();
		}
	
		return root;
	};

} // namespace seakgXMLInterface
