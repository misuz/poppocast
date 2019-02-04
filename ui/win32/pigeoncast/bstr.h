#ifndef _BEASTER_H
#define _BEASTER_H

class Beaster
{
public:
	Beaster();
	Beaster(LPCTSTR r);
	~Beaster();
	void Set(LPCTSTR r);
	void Clear();

	BSTR m_buf;
};

#endif	// _BEASTER_H
