import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.mem.MemoryBlock;
import java.nio.file.*;
import java.io.*;
import java.util.*;

public class ExportFunctionInventory extends GhidraScript {
    String clean(String value) { return value.replace('\t',' ').replace('\n',' ').replace('\r',' '); }
    String hex(long n) { return Long.toHexString(n); }
    @Override
    protected void run() throws Exception {
        String expected = getScriptArgs()[0];
        if (!expected.equalsIgnoreCase(currentProgram.getExecutableSHA256())) throw new IllegalArgumentException("Input hash differs: "+currentProgram.getExecutableSHA256());
        Path dest = Paths.get(getScriptArgs()[1]);
        Path tmp = Paths.get(getScriptArgs()[1]+".tmp");
        SymbolTable sym = currentProgram.getSymbolTable();
        long base = currentProgram.getImageBase().getOffset();
        try (BufferedWriter out=Files.newBufferedWriter(tmp)) {
            out.write("#sha256="+expected+"\n#base="+hex(base)+"\n#language="+currentProgram.getLanguageID()+"\n");
            out.write("rva\tname\tsource\tentry_export\tthunk\tinline\tnoreturn\tranges_rva_inclusive\taliases\tblock\n");
            FunctionIterator it = currentProgram.getFunctionManager().getFunctions(true);
            while (it.hasNext()) {
                monitor.checkCancelled(); Function f=it.next(); Address e=f.getEntryPoint();
                List<String> spans=new ArrayList<>(), labels=new ArrayList<>();
                for(AddressRange r:f.getBody().getAddressRanges()) spans.add(hex(r.getMinAddress().getOffset()-base)+"-"+hex(r.getMaxAddress().getOffset()-base));
                for(Symbol s:sym.getSymbols(e)) labels.add(clean(s.getName(true)));
                MemoryBlock block = currentProgram.getMemory().getBlock(e);
                out.write(String.join("\t",hex(e.getOffset()-base),clean(f.getName(true)),f.getSymbol().getSource().toString(),String.valueOf(sym.isExternalEntryPoint(e)),String.valueOf(f.isThunk()),String.valueOf(f.isInline()),String.valueOf(f.hasNoReturn()),String.join(",",spans),String.join("|",labels),block==null?"":block.getName()));out.newLine();
            }
        }
        Files.move(tmp,dest,StandardCopyOption.REPLACE_EXISTING); println("SCCT native function inventory wrote "+dest);
    }
}
