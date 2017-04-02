#include <arkhe/osgi/core/BinaryFileDescriptor.hpp>



osgi::core::BinaryFileDescriptorPrivate::BinaryFileDescriptorPrivate()
{
  this->BFD = 0;
}

void* osgi::core::BinaryFileDescriptorPrivate::resolve(const char * symbol)
{
    if (!this->BFD)
    {
        return (0);
    }

    void *addr = 0;
/*  
  // Get the symbol table
    long storageNeeded = bfd_get_symtab_upper_bound(this->BFD);
    asymbol ** symbolTable = reinterpret_cast<asymbol **>(malloc(storageNeeded));
  
    long numberOfSymbols = bfd_canonicalize_symtab(this->BFD, symbolTable);
    
    // Run through the symbol table, looking for the requested symbol
    for (int i = 0; i < numberOfSymbols; i++) 
    {
        if (strcmp(symbol, symbolTable[i]->name) == 0)
        { 
            // Found the symbol, get the section pointer
            asection *p = bfd_get_section(symbolTable[i]);
          
            // Do we have this section already?
            MemorySectionContainer::iterator sit;
            for (sit = this->Sections.begin(); sit != this->Sections.end(); ++sit)
            {
                if ((*sit).first == p)
                {
                    break;
                }  
            }
            
            PTR mem;
            if (sit == this->Sections.end())
            {
                // Get the contents of the section
                bfd_size_type sz = bfd_get_section_size (p);
                mem = malloc (sz);
                if (::bfd_get_section_contents(this->BFD, p, mem, static_cast<file_ptr>(0), sz))
                {
                    this->Sections.push_back( MemorySectionType(p, mem) );
                }
                else
                {
                    // Error reading section
                    free(mem);
                    break;
                }
            }
            else
            {
                // pull the start of the section block from the cache
                mem = const_cast<void*>((*sit).second);
            }
            
            // determine the address of this section
            addr = reinterpret_cast<char *>(mem) + (bfd_asymbol_value(symbolTable[i]) - bfd_asymbol_base(symbolTable[i]));
            break;
        }
    }

    // cleanup. just delete the outer vector for the symbol table
    free(symbolTable);
  
    return (addr);
    */
}


osgi::core::BinaryFileDescriptor::BinaryFileDescriptor()
: d_ptr(new BinaryFileDescriptorPrivate)
{
}

osgi::core::BinaryFileDescriptor::BinaryFileDescriptor(const QString& _fileName): 
  d_ptr(new BinaryFileDescriptorPrivate)
{
    Q_D(BinaryFileDescriptor);
    d->FileName = _fileName;
}

osgi::core::BinaryFileDescriptor::~BinaryFileDescriptor()
{
}


GET_CPP(osgi::core::BinaryFileDescriptor, QString, fileName, FileName)
SET_CPP(osgi::core::BinaryFileDescriptor, const QString&, setFileName, FileName)

bool osgi::core::BinaryFileDescriptor::isLoaded() const
{
  Q_D(const BinaryFileDescriptor);
  return (d->BFD != 0);
}

bool osgi::core::BinaryFileDescriptor::load()
{
    Q_D(BinaryFileDescriptor);
 /* 
    bfd_init();
    bfd * abfd = bfd_openr(d->FileName.toLatin1(), NULL);
    
    if (!abfd)
    {
        return false;
    }
  
    //*! make sure it's an object file 
    if (!bfd_check_format (abfd, bfd_object)) 
    {
        bfd_close(abfd);
        return (false);
    }
  
    d->BFD = abfd;
    */
    return (true);
}


bool osgi::core::BinaryFileDescriptor::unload()
{
    Q_D(BinaryFileDescriptor);

    if (d->BFD)
    {
        //bfd_close(d->BFD);
        d->BFD = 0; 
    }

    return (true);
}

void* osgi::core::BinaryFileDescriptor::resolve(const char * symbol)
{
    Q_D(BinaryFileDescriptor);
    return (d->resolve(symbol));
}
