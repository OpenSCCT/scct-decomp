import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
import java.nio.file.*;

public class SeedAuthenticatedEntries extends GhidraScript {
    @Override protected void run() throws Exception {
        String[] args=getScriptArgs();
        if (!args[0].equalsIgnoreCase(currentProgram.getExecutableSHA256())) throw new IllegalArgumentException("SHA256 mismatch");
        int created=0, existing=0, conflict=0, failed=0;
        for(String s:Files.readAllLines(Paths.get(args[1]))) {
            monitor.checkCancelled(); Address a=currentProgram.getImageBase().add(Long.parseLong(s,16));
            if(getFunctionAt(a)!=null) {existing++;continue;}
            if(getFunctionContaining(a)!=null || (getInstructionContaining(a)!=null && getInstructionAt(a)==null)) {conflict++;continue;}
            if(getInstructionAt(a)==null && !disassemble(a)) {failed++;continue;}
            try {if(createFunction(a,null)!=null) created++;else failed++;}catch(RuntimeException e){failed++;}
        }
        println("SCCT validated entry seeds: "+created+" functions created, "+existing+" existing, "+conflict+" existing-range conflicts, "+failed+" failures");
    }
}
