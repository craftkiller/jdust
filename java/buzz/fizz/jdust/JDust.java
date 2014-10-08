/**
 * Copyright (c) 2014 Tom Alexander; Released under the ISC License
 * https://github.com/craftkiller/jdust
 */
package buzz.fizz.jdust;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class JDust
{

    private native int compileTemplate(JState state, String fullDust, String dustTemplate, String templateName);
    private native int renderCompiledTemplate(JState state, String coreDust, String compiledTemplate, String dustContext, String templateName);
    private native int renderTemplate(JState state, String fullDust, String dustTemplate, String dustContext);
    
    private static String readFile(String path)
    {
        Path p = Paths.get(path);
        try 
        {
            byte[] rawData = Files.readAllBytes(p);
            return new String(rawData);
        } catch (IOException e) {
            System.out.println("Error loading " + path);
        }
        return "";
    }

    public static void main(String[] args)
    {
        String out = new JDust().renderDust(readFile(args[0]), readFile(args[1]), "{'title': 'Hello Title'}");
        System.out.println(out);
    }
    
    private String renderDust(String fullDust, String dustTemplate, String dustContext)
    {
        JState state = new JState();
        int status = renderTemplate(state, fullDust, dustTemplate, dustContext);
        return state.getOut();
    }

    static
    {
        System.loadLibrary("JDust");
    }

}
