#include "stdafx.h"
#include "bstr.h"

// Make a new Beaster object
Beaster::Beaster() {

	// No memory allocated, just the BSTR pointed at NULL
	m_buf = NULL;
}

// Takes a poiner to a string of text
// Make a new Beaster object with the text
Beaster::Beaster(LPCTSTR r) {

	// Initialize the BSTR to null, and then set it with the text
	m_buf = NULL;
	Set(r);
}

// Delete the Beaster object
Beaster::~Beaster() {

	// Clear the BSTR, freeing its memory
	Clear();
}

// Takes a pointer to a string of text
// Sets the BSTR in the object with the text
void Beaster::Set(LPCTSTR r) {

	// Clear the BSTR, freeing its memory
	Clear();

	// Convert the text into wide characters
	WCHAR bay[MAX_PATH];
	int result = MultiByteToWideChar(
		CP_ACP,    // Translate from the ANSI code page
		0,         // No options
		r,         // Source text
		-1,        // The text is null-terminated, find its length that way
		bay,       // wide-character buffer
		MAX_PATH); // size of the buffer in wide characters

	// Use the wide characters to allocate a new BSTR
	m_buf = SysAllocString(bay);
}

// Clears the BSTR, freeing its memory
void Beaster::Clear() {

	// If the BSTR points to allocated memory, free it and set it back to NULL
	if (m_buf) { SysFreeString(m_buf); m_buf = NULL; }
}
