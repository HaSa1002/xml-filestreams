#pragma once
#ifndef AF_XML
#define AF_XML
#include "general.h"
#include <vector>

namespace af {
	
	////////////////////////////////////////////////////////////
	/// <summary>Handles XML-Files</summary>
	///
	////////////////////////////////////////////////////////////
	class XML {
	public:
		
		////////////////////////////////////////////////////////////
		/// <summary>Represents a the attributes of a tag</summary>
		///
		////////////////////////////////////////////////////////////
		struct Attribute {
			std::string name;		/// <value>The name of the attribute</value>
			std::string content;	/// <value>the content of the attribute</value>

			////////////////////////////////////////////////////////////
			/// <summary>Checks if to Attribute objects are identical</summary>
			///
			////////////////////////////////////////////////////////////
			bool operator==(const Attribute &right);

			////////////////////////////////////////////////////////////
			/// <summary>Checks if to Structure objects aren't identical</summary>
			///
			////////////////////////////////////////////////////////////
			bool operator!=(const Attribute &right);
		};

		////////////////////////////////////////////////////////////
		/// <summary>Represents a XML File</summary>
		///
		////////////////////////////////////////////////////////////
		struct Structure {
			std::string key;							/// <value>The name of a tag</value>
			std::vector<af::XML::Attribute> attributes;	/// <value>A vector of attributes</value>
			std::string content;						/// <value>the content</value>
			std::vector<af::XML::Structure> childs;		/// <value>a vector of child elements</value>

			////////////////////////////////////////////////////////////
			/// <summary>Checks if to Structure objects are identical</summary>
			///
			////////////////////////////////////////////////////////////
			bool operator==(const Structure &right);
		};

		////////////////////////////////////////////////////////////
		/// <summary>Opens a file</summary>
		///
		/// <param name="filepath">Refrence to the file, which should be opend</param>
		///
		/// <remarks>If you need to create the file first use the default constructor instead and call XML::create</remarks>
		///
		////////////////////////////////////////////////////////////
		XML(const std::string& filepath);

		////////////////////////////////////////////////////////////
		/// <summary>Default constructor</summary>
		///
		////////////////////////////////////////////////////////////
		XML();

		////////////////////////////////////////////////////////////
		/// <summary>Default Deconstructor, but closes the file</summary>
		///
		////////////////////////////////////////////////////////////
		~XML();

		////////////////////////////////////////////////////////////
		/// <summary>Opens a file</summary>
		///
		/// <param name="path">filepath</param>
		///
		/// <exception cref="af::Exception">when the file don't exists</exception>
		///
		////////////////////////////////////////////////////////////
		void open(const std::string& path);

		////////////////////////////////////////////////////////////
		/// <summary>Creates a file</summary>
		///
		/// <param name="path">Filepath</param>
		///
		////////////////////////////////////////////////////////////
		void create(const std::string& path);

		////////////////////////////////////////////////////////////
		/// <summary>Close a file</summary>
		///
		////////////////////////////////////////////////////////////
		void close();

		////////////////////////////////////////////////////////////
		/// <summary>Reads a file</summary>
		///
		/// <param name="self">defines if it was called recursivly</param>
		///
		/// <returns>A Structure which is the file</returns>
		///
		////////////////////////////////////////////////////////////
		auto read(bool self = false)->Structure;
		
		////////////////////////////////////////////////////////////
		/// <summary>Writes into a file</summary>
		///
		/// <param name="file">The Structure Struct which represents a file</param>
		/// <param name="self">defines if it was called recursivly</param>
		/// <param name="run">defines the tabs, that are put infront
		///
		////////////////////////////////////////////////////////////
		void write(Structure file, bool self = false, unsigned int run = 0);

		////////////////////////////////////////////////////////////
		/// <summary>returns the filestruct that was latestly loaded</summary>
		///
		/// <returns>The latest loaded Filestruct</returns>
		///
		////////////////////////////////////////////////////////////
		auto getFileStruct() -> Structure;

		////////////////////////////////////////////////////////////
		/// <summary>Returns the underlying std::fstream object</summary>
		///
		/// <returns>The std::fstream object</returns>
		///
		////////////////////////////////////////////////////////////
		auto getFile()->std::fstream&;

	private:
		enum class Action {
			r,
			w
		};

		void manage_stream(Action action);
		void eraseSpaces(std::string & line, std::string & buffer);
		
		void skipIf();
		bool checkForEndingTag(Structure & current);
		bool getKey(Structure & dest);
		void getAttribute(Structure & dest);
		bool checkForAttributes();

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		std::string					buffer;			///
		std::string					data;			///
		std::fstream				file;			///
		std::string					filename;		///
		Action						lastAction;		///
		af::XML::Structure			parsedFile;		///
		std::vector<std::string>	tagList;		///

	};
}

#include "Struct.inl"

#endif // !AF_XML

