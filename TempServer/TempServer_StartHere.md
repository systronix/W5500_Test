## TempServer - Start Here

This is an attempt to make a reliable, robust, Temperature Server as an example of how to make any sort of Arduino Ethernet application robust.

### Challenges
## Ethernet Library
- almost no return values from functions, so how do you know if they are succeeding? As a ridiculous test, I can ground the MISO signal (so no data from the WIZnet 850io ever arrives). Guess what? Not a single exception thrown. Can my code tell if I am even still communicating with the WIZnet chip?
- Without the ability to detect malfunctions, it's not possible to write code which will recover from them...
- Missing abilities such as even discovering the remote IP address of an http requester. This addition was done and rejected by the Arduino keepers. Many things seem to be rejected in order to keep it "simple for beginners" and to keep code small so it will run on 15-year old 8-bit AVRs (at the expense of support for the host of new ARM versions). I don't know enough about how gcc handles library options or granularity, but crippling the ability of new technology just to maintain backwards compatability with old technology (if that is indeed what is happening) seems ridiculous.
- Can't tell how many sockets are open and other measures of current status of the Ethernet connection(s)
- If the core SPI is like Wire, we have reason to worry about that level in the stack of layers under Ethernet: is SPI part of the problem?
- It's like Wire vs i2c_t3 all over again except where is the more capable, robust Ethernet library? I've googled around and I don't see one.
