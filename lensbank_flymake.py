#!/usr/bin/python
from operator import itemgetter
from optparse import OptionParser


class LensBank(object):

    def __init__(self, filename='lenses.txt', bank=None):
        self.bank = bank or {}
        self.perms = []
        self.perm_count = None
        if filename:
            self.load_from_file(filename)            
        self.backup = self.bank.copy()
        self.two_lens_permutations()
        
    def add(self, f, q=1):
        self.bank[f] = q

    def remove(self, f):
        if self.bank[f] > 1:
            self.bank[f] = self.bank[f] - 1
        else:
            self.bank.pop(f)

    def two_lens_permutations(self):
        perms = []
        for lens1, count in self.backup.iteritems():
            self.remove(lens1)
            for lens2, count in self.bank.iteritems():
                perms.append((lens1, lens2))
            self.bank = self.backup.copy()
        self.perms = perms
        self.perm_count = len(perms)

    def load_from_file(self, filename):
        self.bank = dict((float(x) for x in line.split()) for line in file(filename)) 
        
    def __repr__(self):
        return ''.join("f=%s    Count: %s\n" % (lens, count) for lens, count in self.bank.iteritems()) 




def main():
    usage = "usage: %prog [options] input_file"
    description = "Lens Bank Permutter"
    parser = OptionParser(usage=usage, description=description)
    parser.add_option("-f", "--freq", help="set frequency of laser in nm", type="float")
    (options, args) = parser.parse_args()
    return (options, args)
    

if __name__ == "__main__":
    options, args = main()
    filename  = "lenses.txt" #args[0]
    bank = LensBank(filename)
    print bank.perm_count
    for f1,f2 in bank.perms:
        print "%d %d" % (f1, f2)




