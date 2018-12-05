#pragma once
#ifndef AF_XML
#define AF_XML
#include "general.hpp"
#include <vector>
#include <map>

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
		using Attribute = std::pair<std::string, std::string>;

		////////////////////////////////////////////////////////////
		/// <summary>Represents a XML File</summary>
		///
		////////////////////////////////////////////////////////////
		struct Structure {
			std::string key;							///< The name of a tag
			std::map<std::string, std::string> attributes;	///< A vector of attributes
			std::string content;						///< the content
			std::vector<af::XML::Structure> childs;		///< a vector of child elements

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
		/// <summary>Close a file</summary>
		///
		////////////////////////////////////////////////////////////
		void close();

		////////////////////////////////////////////////////////////
		/// <summary>Creates a file</summary>
		///
		/// <param name="path">Filepath</param>
		///
		////////////////////////////////////////////////////////////
		void create(const std::string& path);

		////////////////////////////////////////////////////////////
		/// <summary>Returns the underlying std::fstream object</summary>
		///
		/// <returns>The std::fstream object</returns>
		///
		////////////////////////////////////////////////////////////
		auto getFile()->std::fstream&;

		////////////////////////////////////////////////////////////
		/// <summary>returns the filestruct that was latestly loaded</summary>
		///
		/// <returns>The latest loaded Filestruct</returns>
		///
		////////////////////////////////////////////////////////////
		auto getFileStruct()->Structure;

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
		/// <param name="run">defines the tabs, that are put infront</param>
		///
		////////////////////////////////////////////////////////////
		void write(Structure file, bool self = false, unsigned int run = 0);

		std::string& getBuffer();

	private:

		////////////////////////////////////////////////////////////
		/// <summary>Defines the filestream action</summary>
		///
		////////////////////////////////////////////////////////////
		enum class Action {
			r,	///< read
			w	///< write
		};

		////////////////////////////////////////////////////////////
		/// <summary> manages the filestream direction </summary>
		///
		/// <param name="action">Action value</param>
		///
		////////////////////////////////////////////////////////////
		void manage_stream(Action action);

		////////////////////////////////////////////////////////////
		/// <summary> erases spaces and tabs in front of a line</summary>
		///
		/// <param name="source">String of the unformatted source</param>
		/// <param name="destination">String where the line goes into</param>
		///
		////////////////////////////////////////////////////////////
		void eraseSpaces(std::string& source, std::string& destination);
		
		////////////////////////////////////////////////////////////
		/// <summary>Checks if buffer is empty</summary>
		///
		/// <exception cref="af::Exception::EmptyLine">line is empty</exception>
		///
		////////////////////////////////////////////////////////////
		void skipIf();

		////////////////////////////////////////////////////////////
		/// <summary>consumes the ending tag if given</summary>
		///
		/// <exception cref=="af::Exception::FoundUnexpectedEndingTag"></exception>
		///
		/// <returns> True if tag (key) consumed </returns>
		///
		////////////////////////////////////////////////////////////
		bool checkForEndingTag();

		////////////////////////////////////////////////////////////
		/// <summary>consumes the key</summary>
		///
		/// <param name="destination">the working Structure object</param>
		///
		/// <returns>True if no attributes included</returns>
		///
		////////////////////////////////////////////////////////////
		bool getKey(Structure & destination);

		////////////////////////////////////////////////////////////
		/// <summary>consumes an Attribute</summary>
		///
		/// <param name="destination">the working Structure object</param>
		///
		////////////////////////////////////////////////////////////
		void getAttribute(Structure & destination);

		////////////////////////////////////////////////////////////
		/// <summary>Checks if Attributes are left</summary>
		///
		/// <returns> True if attributes left</returns>
		///
		////////////////////////////////////////////////////////////
		bool checkForAttributes();

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		std::string					buffer;			///< The working buffer
		std::string					data;			///< The input buffer
		std::fstream				file;			///< The filestream object
		std::string					filename;		///< Filename
		Action						lastAction;		///< last action performed on fstream
		af::XML::Structure			parsedFile;		///< Structure object of the file
		std::vector<std::string>	tagList;		///< saves the opend tags (keys)
	};
}

#include "Struct.inl"

#endif // !AF_XML

