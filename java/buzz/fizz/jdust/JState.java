/**
 * Copyright (c) 2014 Tom Alexander; Released under the ISC License
 * https://github.com/craftkiller/jdust
 */
package buzz.fizz.jdust;

public class JState
{
    private final StringBuilder stdout = new StringBuilder();
    private final StringBuilder stderr = new StringBuilder();
    private final StringBuilder log = new StringBuilder();

    /**
     * Appends the raw string to the output buffer
     */
    public void out(String val)
    {
        stdout.append(val);
    }

    /**
     * Appends the error and a newline to the error buffer
     */
    public void error(String val)
    {
        stderr.append(val);
    }

    /**
     * Appends the message and a new line to the log buffer
     */
    public void log(String val)
    {
        log.append(val);
    }
    
    /**
     * Get the stdout output
     */
    public String getOut()
    {
        return stdout.toString();
    }
    
    /**
     * Get the errors
     */
    public String getError()
    {
        return stderr.toString();
    }
    
    /**
     * Get anything passed to console.log()
     */
    public String getLog()
    {
        return log.toString();
    }
}
