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

    private native int executeJs(JState state, String js);

    public static void main(String[] args)
    {
        String out = new JDust().renderDust(args);
        System.out.println(out);
    }
    
    private String renderDust(String[] files)
    {
        JState state = new JState();
        StringBuilder buffer = new StringBuilder();
        for (String f : files)
        {
            Path p = Paths.get(f);
            try 
            {
                byte[] data = Files.readAllBytes(p);
                String sData = new String(data);
                buffer.append(sData);
                
            } catch (IOException e) {
                System.out.println("Error loading " + f);
            }
        }
        int status = executeJs(state, buffer.toString());
        return state.getOut();
    }

    static
    {
        System.loadLibrary("JDust");
    }

}
