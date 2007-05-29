/***********************************************
* Highlight Table Cells Script- © Dynamic Drive DHTML code library (www.dynamicdrive.com)
* Visit http://www.dynamicDrive.com for hundreds of DHTML scripts
* This notice must stay intact for legal use
***********************************************/

/* Modified by rainbru.free.fr to keep and restore the color
 * in lastColor var.
 *
 *
 */

//Specify highlight behavior. 
//"TD" to highlight table cells, 
//"TR" to highlight the entire row:

var highlightbehavior="TR"

var ns6=document.getElementById&&!document.all
var ie=document.all

var lastColor;

function changeto(e,highlightcolor){
    source=ie? event.srcElement : e.target
    if (source.tagName=="TABLE")
        return
    while(source.tagName!=highlightbehavior && source.tagName!="HTML")
	source=ns6? source.parentNode : source.parentElement
    if (source.style.backgroundColor!=highlightcolor&&source.id!="ignore"){
        lastColor=source.style.backgroundColor
        source.style.backgroundColor=highlightcolor	

    }

    if (source.id!="ignore")
        document.body.style.cursor='pointer'
}

function contains_ns6(master, slave) { 
    //check if slave is contained by master
    while (slave.parentNode)
        if ((slave = slave.parentNode) == master)
	return true;
    return false;
}

function changeback(e){
    if (ie&&(event.fromElement.contains(event.toElement)||source.contains(event.toElement)||source.id=="ignore")||source.tagName=="TABLE")
        return
    else if (ns6&&(contains_ns6(source, e.relatedTarget)||source.id=="ignore"))
        return
    if (ie&&event.toElement!=source||ns6&&e.relatedTarget!=source)
        source.style.backgroundColor=lastColor

    if (source.id!="ignore")
        document.body.style.cursor='auto'

}