In this implementation of session recording, current time is also being logged with every key stroke. This would also give us an idea of what user was doing at a particular time.

(Another idea is to use constuctor destructor, but this would only record end points of session, and I need to figure out how to close application such that destructor is called at the end.)