#include "capturer.h"

KeyCapturer::KeyCapturer()
{

}

KeyCapturer::~KeyCapturer()
{

}


void KeyCapturer::setkeyValue(int key)
{
	emit getKey(key);
}
