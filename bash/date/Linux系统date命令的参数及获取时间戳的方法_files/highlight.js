/*!
  Highlight.js v11.4.0 (git: 2d0e7c1094)
  (c) 2006-2022 Ivan Sagalaev and other contributors
  License: BSD-3-Clause
 */
var hljs=function(){"use strict";var e={exports:{}};function n(e){
return e instanceof Map?e.clear=e.delete=e.set=()=>{
throw Error("map is read-only")}:e instanceof Set&&(e.add=e.clear=e.delete=()=>{
throw Error("set is read-only")
}),Object.freeze(e),Object.getOwnPropertyNames(e).forEach((s=>{var t=e[s]
;"object"!=typeof t||Object.isFrozen(t)||n(t)})),e}
e.exports=n,e.exports.default=n;var s=e.exports;class t{constructor(e){
void 0===e.data&&(e.data={}),this.data=e.data,this.isMatchIgnored=!1}
ignoreMatch(){this.isMatchIgnored=!0}}function a(e){
return e.replace(/&/g,"&amp;").replace(/</g,"&lt;").replace(/>/g,"&gt;").replace(/"/g,"&quot;").replace(/'/g,"&#x27;")
}function r(e,...n){const s=Object.create(null);for(const n in e)s[n]=e[n]
;return n.forEach((e=>{for(const n in e)s[n]=e[n]})),s}const i=e=>!!e.kind
;class o{constructor(e,n){
this.buffer="",this.classPrefix=n.classPrefix,e.walk(this)}addText(e){
this.buffer+=a(e)}openNode(e){if(!i(e))return;let n=e.kind
;n=e.sublanguage?"language-"+n:((e,{prefix:n})=>{if(e.includes(".")){
const s=e.split(".")
;return[`${n}${s.shift()}`,...s.map(((e,n)=>`${e}${"_".repeat(n+1)}`))].join(" ")
}return`${n}${e}`})(n,{prefix:this.classPrefix}),this.span(n)}closeNode(e){
i(e)&&(this.buffer+="</span>")}value(){return this.buffer}span(e){
this.buffer+=`<span class="${e}">`}}class c{constructor(){this.rootNode={
children:[]},this.stack=[this.rootNode]}get top(){
return this.stack[this.stack.length-1]}get root(){return this.rootNode}add(e){
this.top.children.push(e)}openNode(e){const n={kind:e,children:[]}
;this.add(n),this.stack.push(n)}closeNode(){
if(this.stack.length>1)return this.stack.pop()}closeAllNodes(){
for(;this.closeNode(););}toJSON(){return JSON.stringify(this.rootNode,null,4)}
walk(e){return this.constructor._walk(e,this.rootNode)}static _walk(e,n){
return"string"==typeof n?e.addText(n):n.children&&(e.openNode(n),
n.children.forEach((n=>this._walk(e,n))),e.closeNode(n)),e}static _collapse(e){
"string"!=typeof e&&e.children&&(e.children.every((e=>"string"==typeof e))?e.children=[e.children.join("")]:e.children.forEach((e=>{
c._collapse(e)})))}}class l extends c{constructor(e){super(),this.options=e}
addKeyword(e,n){""!==e&&(this.openNode(n),this.addText(e),this.closeNode())}
addText(e){""!==e&&this.add(e)}addSublanguage(e,n){const s=e.root
;s.kind=n,s.sublanguage=!0,this.add(s)}toHTML(){
return new o(this,this.options).value()}finalize(){return!0}}function d(e){
return RegExp(e.replace(/[-/\\^$*+?.()|[\]{}]/g,"\\$&"),"m")}function p(e){
return e?"string"==typeof e?e:e.source:null}function m(e){return g("(?=",e,")")}
function u(e){return g("(?:",e,")*")}function b(e){return g("(?:",e,")?")}
function g(...e){return e.map((e=>p(e))).join("")}function _(...e){const n=(e=>{
const n=e[e.length-1]
;return"object"==typeof n&&n.constructor===Object?(e.splice(e.length-1,1),n):{}
})(e);return"("+(n.capture?"":"?:")+e.map((e=>p(e))).join("|")+")"}
function v(e){return RegExp(e.toString()+"|").exec("").length-1}
const f=/\[(?:[^\\\]]|\\.)*\]|\(\??|\\([1-9][0-9]*)|\\./
;function h(e,{joinWith:n}){let s=0;return e.map((e=>{s+=1;const n=s
;let t=p(e),a="";for(;t.length>0;){const e=f.exec(t);if(!e){a+=t;break}
a+=t.substring(0,e.index),
t=t.substring(e.index+e[0].length),"\\"===e[0][0]&&e[1]?a+="\\"+(Number(e[1])+n):(a+=e[0],
"("===e[0]&&s++)}return a})).map((e=>`(${e})`)).join(n)}
const E="[a-zA-Z]\\w*",w="[a-zA-Z_]\\w*",y="\\b\\d+(\\.\\d+)?",N="(-?)(\\b0[xX][a-fA-F0-9]+|(\\b\\d+(\\.\\d*)?|\\.\\d+)([eE][-+]?\\d+)?)",x="\\b(0b[01]+)",k={
begin:"\\\\[\\s\\S]",relevance:0},O={scope:"string",begin:"'",end:"'",
illegal:"\\n",contains:[k]},M={scope:"string",begin:'"',end:'"',illegal:"\\n",
contains:[k]},S=(e,n,s={})=>{const t=r({scope:"comment",begin:e,end:n,
contains:[]},s);t.contains.push({scope:"doctag",
begin:"[ ]*(?=(TODO|FIXME|NOTE|BUG|OPTIMIZE|HACK|XXX):)",
end:/(TODO|FIXME|NOTE|BUG|OPTIMIZE|HACK|XXX):/,excludeBegin:!0,relevance:0})
;const a=_("I","a","is","so","us","to","at","if","in","it","on",/[A-Za-z]+['](d|ve|re|ll|t|s|n)/,/[A-Za-z]+[-][a-z]+/,/[A-Za-z][a-z]{2,}/)
;return t.contains.push({begin:g(/[ ]+/,"(",a,/[.]?[:]?([.][ ]|[ ])/,"){3}")}),t
},C=S("//","$"),A=S("/\\*","\\*/"),T=S("#","$");var $=Object.freeze({
__proto__:null,MATCH_NOTHING_RE:/\b\B/,IDENT_RE:E,UNDERSCORE_IDENT_RE:w,
NUMBER_RE:y,C_NUMBER_RE:N,BINARY_NUMBER_RE:x,
RE_STARTERS_RE:"!|!=|!==|%|%=|&|&&|&=|\\*|\\*=|\\+|\\+=|,|-|-=|/=|/|:|;|<<|<<=|<=|<|===|==|=|>>>=|>>=|>=|>>>|>>|>|\\?|\\[|\\{|\\(|\\^|\\^=|\\||\\|=|\\|\\||~",
SHEBANG:(e={})=>{const n=/^#![ ]*\//
;return e.binary&&(e.begin=g(n,/.*\b/,e.binary,/\b.*/)),r({scope:"meta",begin:n,
end:/$/,relevance:0,"on:begin":(e,n)=>{0!==e.index&&n.ignoreMatch()}},e)},
BACKSLASH_ESCAPE:k,APOS_STRING_MODE:O,QUOTE_STRING_MODE:M,PHRASAL_WORDS_MODE:{
begin:/\b(a|an|the|are|I'm|isn't|don't|doesn't|won't|but|just|should|pretty|simply|enough|gonna|going|wtf|so|such|will|you|your|they|like|more)\b/
},COMMENT:S,C_LINE_COMMENT_MODE:C,C_BLOCK_COMMENT_MODE:A,HASH_COMMENT_MODE:T,
NUMBER_MODE:{scope:"number",begin:y,relevance:0},C_NUMBER_MODE:{scope:"number",
begin:N,relevance:0},BINARY_NUMBER_MODE:{scope:"number",begin:x,relevance:0},
REGEXP_MODE:{begin:/(?=\/[^/\n]*\/)/,contains:[{scope:"regexp",begin:/\//,
end:/\/[gimuy]*/,illegal:/\n/,contains:[k,{begin:/\[/,end:/\]/,relevance:0,
contains:[k]}]}]},TITLE_MODE:{scope:"title",begin:E,relevance:0},
UNDERSCORE_TITLE_MODE:{scope:"title",begin:w,relevance:0},METHOD_GUARD:{
begin:"\\.\\s*[a-zA-Z_]\\w*",relevance:0},END_SAME_AS_BEGIN:e=>Object.assign(e,{
"on:begin":(e,n)=>{n.data._beginMatch=e[1]},"on:end":(e,n)=>{
n.data._beginMatch!==e[1]&&n.ignoreMatch()}})});function q(e,n){
"."===e.input[e.index-1]&&n.ignoreMatch()}function R(e,n){
void 0!==e.className&&(e.scope=e.className,delete e.className)}function D(e,n){
n&&e.beginKeywords&&(e.begin="\\b("+e.beginKeywords.split(" ").join("|")+")(?!\\.)(?=\\b|\\s)",
e.__beforeBegin=q,e.keywords=e.keywords||e.beginKeywords,delete e.beginKeywords,
void 0===e.relevance&&(e.relevance=0))}function I(e,n){
Array.isArray(e.illegal)&&(e.illegal=_(...e.illegal))}function L(e,n){
if(e.match){
if(e.begin||e.end)throw Error("begin & end are not supported with match")
;e.begin=e.match,delete e.match}}function B(e,n){
void 0===e.relevance&&(e.relevance=1)}const z=(e,n)=>{if(!e.beforeMatch)return
;if(e.starts)throw Error("beforeMatch cannot be used with starts")
;const s=Object.assign({},e);Object.keys(e).forEach((n=>{delete e[n]
})),e.keywords=s.keywords,e.begin=g(s.beforeMatch,m(s.begin)),e.starts={
relevance:0,contains:[Object.assign(s,{endsParent:!0})]
},e.relevance=0,delete s.beforeMatch
},U=["of","and","for","in","not","or","if","then","parent","list","value"]
;function F(e,n,s="keyword"){const t=Object.create(null)
;return"string"==typeof e?a(s,e.split(" ")):Array.isArray(e)?a(s,e):Object.keys(e).forEach((s=>{
Object.assign(t,F(e[s],n,s))})),t;function a(e,s){
n&&(s=s.map((e=>e.toLowerCase()))),s.forEach((n=>{const s=n.split("|")
;t[s[0]]=[e,P(s[0],s[1])]}))}}function P(e,n){
return n?Number(n):(e=>U.includes(e.toLowerCase()))(e)?0:1}const j={},K=e=>{
console.error(e)},H=(e,...n)=>{console.log("WARN: "+e,...n)},Z=(e,n)=>{
j[`${e}/${n}`]||(console.log(`Deprecated as of ${e}. ${n}`),j[`${e}/${n}`]=!0)
},G=Error();function W(e,n,{key:s}){let t=0;const a=e[s],r={},i={}
;for(let e=1;e<=n.length;e++)i[e+t]=a[e],r[e+t]=!0,t+=v(n[e-1])
;e[s]=i,e[s]._emit=r,e[s]._multi=!0}function Q(e){(e=>{
e.scope&&"object"==typeof e.scope&&null!==e.scope&&(e.beginScope=e.scope,
delete e.scope)})(e),"string"==typeof e.beginScope&&(e.beginScope={
_wrap:e.beginScope}),"string"==typeof e.endScope&&(e.endScope={_wrap:e.endScope
}),(e=>{if(Array.isArray(e.begin)){
if(e.skip||e.excludeBegin||e.returnBegin)throw K("skip, excludeBegin, returnBegin not compatible with beginScope: {}"),
G
;if("object"!=typeof e.beginScope||null===e.beginScope)throw K("beginScope must be object"),
G;W(e,e.begin,{key:"beginScope"}),e.begin=h(e.begin,{joinWith:""})}})(e),(e=>{
if(Array.isArray(e.end)){
if(e.skip||e.excludeEnd||e.returnEnd)throw K("skip, excludeEnd, returnEnd not compatible with endScope: {}"),
G
;if("object"!=typeof e.endScope||null===e.endScope)throw K("endScope must be object"),
G;W(e,e.end,{key:"endScope"}),e.end=h(e.end,{joinWith:""})}})(e)}function X(e){
function n(n,s){
return RegExp(p(n),"m"+(e.case_insensitive?"i":"")+(e.unicodeRegex?"u":"")+(s?"g":""))
}class s{constructor(){
this.matchIndexes={},this.regexes=[],this.matchAt=1,this.position=0}
addRule(e,n){
n.position=this.position++,this.matchIndexes[this.matchAt]=n,this.regexes.push([n,e]),
this.matchAt+=v(e)+1}compile(){0===this.regexes.length&&(this.exec=()=>null)
;const e=this.regexes.map((e=>e[1]));this.matcherRe=n(h(e,{joinWith:"|"
}),!0),this.lastIndex=0}exec(e){this.matcherRe.lastIndex=this.lastIndex
;const n=this.matcherRe.exec(e);if(!n)return null
;const s=n.findIndex(((e,n)=>n>0&&void 0!==e)),t=this.matchIndexes[s]
;return n.splice(0,s),Object.assign(n,t)}}class t{constructor(){
this.rules=[],this.multiRegexes=[],
this.count=0,this.lastIndex=0,this.regexIndex=0}getMatcher(e){
if(this.multiRegexes[e])return this.multiRegexes[e];const n=new s
;return this.rules.slice(e).forEach((([e,s])=>n.addRule(e,s))),
n.compile(),this.multiRegexes[e]=n,n}resumingScanAtSamePosition(){
return 0!==this.regexIndex}considerAll(){this.regexIndex=0}addRule(e,n){
this.rules.push([e,n]),"begin"===n.type&&this.count++}exec(e){
const n=this.getMatcher(this.regexIndex);n.lastIndex=this.lastIndex
;let s=n.exec(e)
;if(this.resumingScanAtSamePosition())if(s&&s.index===this.lastIndex);else{
const n=this.getMatcher(0);n.lastIndex=this.lastIndex+1,s=n.exec(e)}
return s&&(this.regexIndex+=s.position+1,
this.regexIndex===this.count&&this.considerAll()),s}}
if(e.compilerExtensions||(e.compilerExtensions=[]),
e.contains&&e.contains.includes("self"))throw Error("ERR: contains `self` is not supported at the top-level of a language.  See documentation.")
;return e.classNameAliases=r(e.classNameAliases||{}),function s(a,i){const o=a
;if(a.isCompiled)return o
;[R,L,Q,z].forEach((e=>e(a,i))),e.compilerExtensions.forEach((e=>e(a,i))),
a.__beforeBegin=null,[D,I,B].forEach((e=>e(a,i))),a.isCompiled=!0;let c=null
;return"object"==typeof a.keywords&&a.keywords.$pattern&&(a.keywords=Object.assign({},a.keywords),
c=a.keywords.$pattern,
delete a.keywords.$pattern),c=c||/\w+/,a.keywords&&(a.keywords=F(a.keywords,e.case_insensitive)),
o.keywordPatternRe=n(c,!0),
i&&(a.begin||(a.begin=/\B|\b/),o.beginRe=n(o.begin),a.end||a.endsWithParent||(a.end=/\B|\b/),
a.end&&(o.endRe=n(o.end)),
o.terminatorEnd=p(o.end)||"",a.endsWithParent&&i.terminatorEnd&&(o.terminatorEnd+=(a.end?"|":"")+i.terminatorEnd)),
a.illegal&&(o.illegalRe=n(a.illegal)),
a.contains||(a.contains=[]),a.contains=[].concat(...a.contains.map((e=>(e=>(e.variants&&!e.cachedVariants&&(e.cachedVariants=e.variants.map((n=>r(e,{
variants:null},n)))),e.cachedVariants?e.cachedVariants:V(e)?r(e,{
starts:e.starts?r(e.starts):null
}):Object.isFrozen(e)?r(e):e))("self"===e?a:e)))),a.contains.forEach((e=>{s(e,o)
})),a.starts&&s(a.starts,i),o.matcher=(e=>{const n=new t
;return e.contains.forEach((e=>n.addRule(e.begin,{rule:e,type:"begin"
}))),e.terminatorEnd&&n.addRule(e.terminatorEnd,{type:"end"
}),e.illegal&&n.addRule(e.illegal,{type:"illegal"}),n})(o),o}(e)}function V(e){
return!!e&&(e.endsWithParent||V(e.starts))}class Y extends Error{
constructor(e,n){super(e),this.name="HTMLInjectionError",this.html=n}}
const J=a,ee=r,ne=Symbol("nomatch");var se=(e=>{
const n=Object.create(null),a=Object.create(null),r=[];let i=!0
;const o="Could not find the language '{}', did you forget to load/include a language module?",c={
disableAutodetect:!0,name:"Plain text",contains:[]};let d={
ignoreUnescapedHTML:!1,throwUnescapedHTML:!1,noHighlightRe:/^(no-?highlight)$/i,
languageDetectRe:/\blang(?:uage)?-([\w-]+)\b/i,classPrefix:"hljs-",
cssSelector:"pre code",languages:null,__emitter:l};function p(e){
return d.noHighlightRe.test(e)}function v(e,n,s){let t="",a=""
;"object"==typeof n?(t=e,
s=n.ignoreIllegals,a=n.language):(Z("10.7.0","highlight(lang, code, ...args) has been deprecated."),
Z("10.7.0","Please use highlight(code, options) instead.\nhttps://github.com/highlightjs/highlight.js/issues/2277"),
a=e,t=n),void 0===s&&(s=!0);const r={code:t,language:a};O("before:highlight",r)
;const i=r.result?r.result:f(r.language,r.code,s)
;return i.code=r.code,O("after:highlight",i),i}function f(e,s,a,r){
const c=Object.create(null);function l(){if(!k.keywords)return void M.addText(S)
;let e=0;k.keywordPatternRe.lastIndex=0;let n=k.keywordPatternRe.exec(S),s=""
;for(;n;){s+=S.substring(e,n.index)
;const a=w.case_insensitive?n[0].toLowerCase():n[0],r=(t=a,k.keywords[t]);if(r){
const[e,t]=r
;if(M.addText(s),s="",c[a]=(c[a]||0)+1,c[a]<=7&&(C+=t),e.startsWith("_"))s+=n[0];else{
const s=w.classNameAliases[e]||e;M.addKeyword(n[0],s)}}else s+=n[0]
;e=k.keywordPatternRe.lastIndex,n=k.keywordPatternRe.exec(S)}var t
;s+=S.substr(e),M.addText(s)}function p(){null!=k.subLanguage?(()=>{
if(""===S)return;let e=null;if("string"==typeof k.subLanguage){
if(!n[k.subLanguage])return void M.addText(S)
;e=f(k.subLanguage,S,!0,O[k.subLanguage]),O[k.subLanguage]=e._top
}else e=h(S,k.subLanguage.length?k.subLanguage:null)
;k.relevance>0&&(C+=e.relevance),M.addSublanguage(e._emitter,e.language)
})():l(),S=""}function m(e,n){let s=1;for(;void 0!==n[s];){if(!e._emit[s]){s++
;continue}const t=w.classNameAliases[e[s]]||e[s],a=n[s]
;t?M.addKeyword(a,t):(S=a,l(),S=""),s++}}function u(e,n){
return e.scope&&"string"==typeof e.scope&&M.openNode(w.classNameAliases[e.scope]||e.scope),
e.beginScope&&(e.beginScope._wrap?(M.addKeyword(S,w.classNameAliases[e.beginScope._wrap]||e.beginScope._wrap),
S=""):e.beginScope._multi&&(m(e.beginScope,n),S="")),k=Object.create(e,{parent:{
value:k}}),k}function b(e,n,s){let a=((e,n)=>{const s=e&&e.exec(n)
;return s&&0===s.index})(e.endRe,s);if(a){if(e["on:end"]){const s=new t(e)
;e["on:end"](n,s),s.isMatchIgnored&&(a=!1)}if(a){
for(;e.endsParent&&e.parent;)e=e.parent;return e}}
if(e.endsWithParent)return b(e.parent,n,s)}function g(e){
return 0===k.matcher.regexIndex?(S+=e[0],1):($=!0,0)}function _(e){
const n=e[0],t=s.substr(e.index),a=b(k,e,t);if(!a)return ne;const r=k
;k.endScope&&k.endScope._wrap?(p(),
M.addKeyword(n,k.endScope._wrap)):k.endScope&&k.endScope._multi?(p(),
m(k.endScope,e)):r.skip?S+=n:(r.returnEnd||r.excludeEnd||(S+=n),
p(),r.excludeEnd&&(S=n));do{
k.scope&&M.closeNode(),k.skip||k.subLanguage||(C+=k.relevance),k=k.parent
}while(k!==a.parent);return a.starts&&u(a.starts,e),r.returnEnd?0:n.length}
let v={};function E(n,r){const o=r&&r[0];if(S+=n,null==o)return p(),0
;if("begin"===v.type&&"end"===r.type&&v.index===r.index&&""===o){
if(S+=s.slice(r.index,r.index+1),!i){const n=Error(`0 width match regex (${e})`)
;throw n.languageName=e,n.badRule=v.rule,n}return 1}
if(v=r,"begin"===r.type)return(e=>{
const n=e[0],s=e.rule,a=new t(s),r=[s.__beforeBegin,s["on:begin"]]
;for(const s of r)if(s&&(s(e,a),a.isMatchIgnored))return g(n)
;return s.skip?S+=n:(s.excludeBegin&&(S+=n),
p(),s.returnBegin||s.excludeBegin||(S=n)),u(s,e),s.returnBegin?0:n.length})(r)
;if("illegal"===r.type&&!a){
const e=Error('Illegal lexeme "'+o+'" for mode "'+(k.scope||"<unnamed>")+'"')
;throw e.mode=k,e}if("end"===r.type){const e=_(r);if(e!==ne)return e}
if("illegal"===r.type&&""===o)return 1
;if(T>1e5&&T>3*r.index)throw Error("potential infinite loop, way more iterations than matches")
;return S+=o,o.length}const w=N(e)
;if(!w)throw K(o.replace("{}",e)),Error('Unknown language: "'+e+'"')
;const y=X(w);let x="",k=r||y;const O={},M=new d.__emitter(d);(()=>{const e=[]
;for(let n=k;n!==w;n=n.parent)n.scope&&e.unshift(n.scope)
;e.forEach((e=>M.openNode(e)))})();let S="",C=0,A=0,T=0,$=!1;try{
for(k.matcher.considerAll();;){
T++,$?$=!1:k.matcher.considerAll(),k.matcher.lastIndex=A
;const e=k.matcher.exec(s);if(!e)break;const n=E(s.substring(A,e.index),e)
;A=e.index+n}return E(s.substr(A)),M.closeAllNodes(),M.finalize(),x=M.toHTML(),{
language:e,value:x,relevance:C,illegal:!1,_emitter:M,_top:k}}catch(n){
if(n.message&&n.message.includes("Illegal"))return{language:e,value:J(s),
illegal:!0,relevance:0,_illegalBy:{message:n.message,index:A,
context:s.slice(A-100,A+100),mode:n.mode,resultSoFar:x},_emitter:M};if(i)return{
language:e,value:J(s),illegal:!1,relevance:0,errorRaised:n,_emitter:M,_top:k}
;throw n}}function h(e,s){s=s||d.languages||Object.keys(n);const t=(e=>{
const n={value:J(e),illegal:!1,relevance:0,_top:c,_emitter:new d.__emitter(d)}
;return n._emitter.addText(e),n})(e),a=s.filter(N).filter(k).map((n=>f(n,e,!1)))
;a.unshift(t);const r=a.sort(((e,n)=>{
if(e.relevance!==n.relevance)return n.relevance-e.relevance
;if(e.language&&n.language){if(N(e.language).supersetOf===n.language)return 1
;if(N(n.language).supersetOf===e.language)return-1}return 0})),[i,o]=r,l=i
;return l.secondBest=o,l}function E(e){let n=null;const s=(e=>{
let n=e.className+" ";n+=e.parentNode?e.parentNode.className:""
;const s=d.languageDetectRe.exec(n);if(s){const n=N(s[1])
;return n||(H(o.replace("{}",s[1])),
H("Falling back to no-highlight mode for this block.",e)),n?s[1]:"no-highlight"}
return n.split(/\s+/).find((e=>p(e)||N(e)))})(e);if(p(s))return
;if(O("before:highlightElement",{el:e,language:s
}),e.children.length>0&&(d.ignoreUnescapedHTML||(console.warn("One of your code blocks includes unescaped HTML. This is a potentially serious security risk."),
console.warn("https://github.com/highlightjs/highlight.js/wiki/security"),
console.warn("The element with unescaped HTML:"),
console.warn(e)),d.throwUnescapedHTML))throw new Y("One of your code blocks includes unescaped HTML.",e.innerHTML)
;n=e;const t=n.textContent,r=s?v(t,{language:s,ignoreIllegals:!0}):h(t)
;e.innerHTML=r.value,((e,n,s)=>{const t=n&&a[n]||s
;e.classList.add("hljs"),e.classList.add("language-"+t)
})(e,s,r.language),e.result={language:r.language,re:r.relevance,
relevance:r.relevance},r.secondBest&&(e.secondBest={
language:r.secondBest.language,relevance:r.secondBest.relevance
}),O("after:highlightElement",{el:e,result:r,text:t})}let w=!1;function y(){
"loading"!==document.readyState?document.querySelectorAll(d.cssSelector).forEach(E):w=!0
}function N(e){return e=(e||"").toLowerCase(),n[e]||n[a[e]]}
function x(e,{languageName:n}){"string"==typeof e&&(e=[e]),e.forEach((e=>{
a[e.toLowerCase()]=n}))}function k(e){const n=N(e)
;return n&&!n.disableAutodetect}function O(e,n){const s=e;r.forEach((e=>{
e[s]&&e[s](n)}))}
"undefined"!=typeof window&&window.addEventListener&&window.addEventListener("DOMContentLoaded",(()=>{
w&&y()}),!1),Object.assign(e,{highlight:v,highlightAuto:h,highlightAll:y,
highlightElement:E,
highlightBlock:e=>(Z("10.7.0","highlightBlock will be removed entirely in v12.0"),
Z("10.7.0","Please use highlightElement now."),E(e)),configure:e=>{d=ee(d,e)},
initHighlighting:()=>{
y(),Z("10.6.0","initHighlighting() deprecated.  Use highlightAll() now.")},
initHighlightingOnLoad:()=>{
y(),Z("10.6.0","initHighlightingOnLoad() deprecated.  Use highlightAll() now.")
},registerLanguage:(s,t)=>{let a=null;try{a=t(e)}catch(e){
if(K("Language definition for '{}' could not be registered.".replace("{}",s)),
!i)throw e;K(e),a=c}
a.name||(a.name=s),n[s]=a,a.rawDefinition=t.bind(null,e),a.aliases&&x(a.aliases,{
languageName:s})},unregisterLanguage:e=>{delete n[e]
;for(const n of Object.keys(a))a[n]===e&&delete a[n]},
listLanguages:()=>Object.keys(n),getLanguage:N,registerAliases:x,
autoDetection:k,inherit:ee,addPlugin:e=>{(e=>{
e["before:highlightBlock"]&&!e["before:highlightElement"]&&(e["before:highlightElement"]=n=>{
e["before:highlightBlock"](Object.assign({block:n.el},n))
}),e["after:highlightBlock"]&&!e["after:highlightElement"]&&(e["after:highlightElement"]=n=>{
e["after:highlightBlock"](Object.assign({block:n.el},n))})})(e),r.push(e)}
}),e.debugMode=()=>{i=!1},e.safeMode=()=>{i=!0
},e.versionString="11.4.0",e.regex={concat:g,lookahead:m,either:_,optional:b,
anyNumberOfTimes:u};for(const e in $)"object"==typeof $[e]&&s($[e])
;return Object.assign(e,$),e})({});const te=e=>({IMPORTANT:{scope:"meta",
begin:"!important"},BLOCK_COMMENT:e.C_BLOCK_COMMENT_MODE,HEXCOLOR:{
scope:"number",begin:/#(([0-9a-fA-F]{3,4})|(([0-9a-fA-F]{2}){3,4}))\b/},
FUNCTION_DISPATCH:{className:"built_in",begin:/[\w-]+(?=\()/},
ATTRIBUTE_SELECTOR_MODE:{scope:"selector-attr",begin:/\[/,end:/\]/,illegal:"$",
contains:[e.APOS_STRING_MODE,e.QUOTE_STRING_MODE]},CSS_NUMBER_MODE:{
scope:"number",
begin:e.NUMBER_RE+"(%|em|ex|ch|rem|vw|vh|vmin|vmax|cm|mm|in|pt|pc|px|deg|grad|rad|turn|s|ms|Hz|kHz|dpi|dpcm|dppx)?",
relevance:0},CSS_VARIABLE:{className:"attr",begin:/--[A-Za-z][A-Za-z0-9_-]*/}
}),ae=["a","abbr","address","article","aside","audio","b","blockquote","body","button","canvas","caption","cite","code","dd","del","details","dfn","div","dl","dt","em","fieldset","figcaption","figure","footer","form","h1","h2","h3","h4","h5","h6","header","hgroup","html","i","iframe","img","input","ins","kbd","label","legend","li","main","mark","menu","nav","object","ol","p","q","quote","samp","section","span","strong","summary","sup","table","tbody","td","textarea","tfoot","th","thead","time","tr","ul","var","video"],re=["any-hover","any-pointer","aspect-ratio","color","color-gamut","color-index","device-aspect-ratio","device-height","device-width","display-mode","forced-colors","grid","height","hover","inverted-colors","monochrome","orientation","overflow-block","overflow-inline","pointer","prefers-color-scheme","prefers-contrast","prefers-reduced-motion","prefers-reduced-transparency","resolution","scan","scripting","update","width","min-width","max-width","min-height","max-height"],ie=["active","any-link","blank","checked","current","default","defined","dir","disabled","drop","empty","enabled","first","first-child","first-of-type","fullscreen","future","focus","focus-visible","focus-within","has","host","host-context","hover","indeterminate","in-range","invalid","is","lang","last-child","last-of-type","left","link","local-link","not","nth-child","nth-col","nth-last-child","nth-last-col","nth-last-of-type","nth-of-type","only-child","only-of-type","optional","out-of-range","past","placeholder-shown","read-only","read-write","required","right","root","scope","target","target-within","user-invalid","valid","visited","where"],oe=["after","backdrop","before","cue","cue-region","first-letter","first-line","grammar-error","marker","part","placeholder","selection","slotted","spelling-error"],ce=["align-content","align-items","align-self","all","animation","animation-delay","animation-direction","animation-duration","animation-fill-mode","animation-iteration-count","animation-name","animation-play-state","animation-timing-function","backface-visibility","background","background-attachment","background-clip","background-color","background-image","background-origin","background-position","background-repeat","background-size","border","border-bottom","border-bottom-color","border-bottom-left-radius","border-bottom-right-radius","border-bottom-style","border-bottom-width","border-collapse","border-color","border-image","border-image-outset","border-image-repeat","border-image-slice","border-image-source","border-image-width","border-left","border-left-color","border-left-style","border-left-width","border-radius","border-right","border-right-color","border-right-style","border-right-width","border-spacing","border-style","border-top","border-top-color","border-top-left-radius","border-top-right-radius","border-top-style","border-top-width","border-width","bottom","box-decoration-break","box-shadow","box-sizing","break-after","break-before","break-inside","caption-side","caret-color","clear","clip","clip-path","clip-rule","color","column-count","column-fill","column-gap","column-rule","column-rule-color","column-rule-style","column-rule-width","column-span","column-width","columns","contain","content","content-visibility","counter-increment","counter-reset","cue","cue-after","cue-before","cursor","direction","display","empty-cells","filter","flex","flex-basis","flex-direction","flex-flow","flex-grow","flex-shrink","flex-wrap","float","flow","font","font-display","font-family","font-feature-settings","font-kerning","font-language-override","font-size","font-size-adjust","font-smoothing","font-stretch","font-style","font-synthesis","font-variant","font-variant-caps","font-variant-east-asian","font-variant-ligatures","font-variant-numeric","font-variant-position","font-variation-settings","font-weight","gap","glyph-orientation-vertical","grid","grid-area","grid-auto-columns","grid-auto-flow","grid-auto-rows","grid-column","grid-column-end","grid-column-start","grid-gap","grid-row","grid-row-end","grid-row-start","grid-template","grid-template-areas","grid-template-columns","grid-template-rows","hanging-punctuation","height","hyphens","icon","image-orientation","image-rendering","image-resolution","ime-mode","isolation","justify-content","left","letter-spacing","line-break","line-height","list-style","list-style-image","list-style-position","list-style-type","margin","margin-bottom","margin-left","margin-right","margin-top","marks","mask","mask-border","mask-border-mode","mask-border-outset","mask-border-repeat","mask-border-slice","mask-border-source","mask-border-width","mask-clip","mask-composite","mask-image","mask-mode","mask-origin","mask-position","mask-repeat","mask-size","mask-type","max-height","max-width","min-height","min-width","mix-blend-mode","nav-down","nav-index","nav-left","nav-right","nav-up","none","normal","object-fit","object-position","opacity","order","orphans","outline","outline-color","outline-offset","outline-style","outline-width","overflow","overflow-wrap","overflow-x","overflow-y","padding","padding-bottom","padding-left","padding-right","padding-top","page-break-after","page-break-before","page-break-inside","pause","pause-after","pause-before","perspective","perspective-origin","pointer-events","position","quotes","resize","rest","rest-after","rest-before","right","row-gap","scroll-margin","scroll-margin-block","scroll-margin-block-end","scroll-margin-block-start","scroll-margin-bottom","scroll-margin-inline","scroll-margin-inline-end","scroll-margin-inline-start","scroll-margin-left","scroll-margin-right","scroll-margin-top","scroll-padding","scroll-padding-block","scroll-padding-block-end","scroll-padding-block-start","scroll-padding-bottom","scroll-padding-inline","scroll-padding-inline-end","scroll-padding-inline-start","scroll-padding-left","scroll-padding-right","scroll-padding-top","scroll-snap-align","scroll-snap-stop","scroll-snap-type","shape-image-threshold","shape-margin","shape-outside","speak","speak-as","src","tab-size","table-layout","text-align","text-align-all","text-align-last","text-combine-upright","text-decoration","text-decoration-color","text-decoration-line","text-decoration-style","text-emphasis","text-emphasis-color","text-emphasis-position","text-emphasis-style","text-indent","text-justify","text-orientation","text-overflow","text-rendering","text-shadow","text-transform","text-underline-position","top","transform","transform-box","transform-origin","transform-style","transition","transition-delay","transition-duration","transition-property","transition-timing-function","unicode-bidi","vertical-align","visibility","voice-balance","voice-duration","voice-family","voice-pitch","voice-range","voice-rate","voice-stress","voice-volume","white-space","widows","width","will-change","word-break","word-spacing","word-wrap","writing-mode","z-index"].reverse(),le=ie.concat(oe)
;var de="\\.([0-9](_*[0-9])*)",pe="[0-9a-fA-F](_*[0-9a-fA-F])*",me={
className:"number",variants:[{
begin:`(\\b([0-9](_*[0-9])*)((${de})|\\.)?|(${de}))[eE][+-]?([0-9](_*[0-9])*)[fFdD]?\\b`
},{begin:`\\b([0-9](_*[0-9])*)((${de})[fFdD]?\\b|\\.([fFdD]\\b)?)`},{
begin:`(${de})[fFdD]?\\b`},{begin:"\\b([0-9](_*[0-9])*)[fFdD]\\b"},{
begin:`\\b0[xX]((${pe})\\.?|(${pe})?\\.(${pe}))[pP][+-]?([0-9](_*[0-9])*)[fFdD]?\\b`
},{begin:"\\b(0|[1-9](_*[0-9])*)[lL]?\\b"},{begin:`\\b0[xX](${pe})[lL]?\\b`},{
begin:"\\b0(_*[0-7])*[lL]?\\b"},{begin:"\\b0[bB][01](_*[01])*[lL]?\\b"}],
relevance:0};function ue(e,n,s){return-1===s?"":e.replace(n,(t=>ue(e,n,s-1)))}
const be="[A-Za-z$_][0-9A-Za-z$_]*",ge=["as","in","of","if","for","while","finally","var","new","function","do","return","void","else","break","catch","instanceof","with","throw","case","default","try","switch","continue","typeof","delete","let","yield","const","class","debugger","async","await","static","import","from","export","extends"],_e=["true","false","null","undefined","NaN","Infinity"],ve=["Object","Function","Boolean","Symbol","Math","Date","Number","BigInt","String","RegExp","Array","Float32Array","Float64Array","Int8Array","Uint8Array","Uint8ClampedArray","Int16Array","Int32Array","Uint16Array","Uint32Array","BigInt64Array","BigUint64Array","Set","Map","WeakSet","WeakMap","ArrayBuffer","SharedArrayBuffer","Atomics","DataView","JSON","Promise","Generator","GeneratorFunction","AsyncFunction","Reflect","Proxy","Intl","WebAssembly"],fe=["Error","EvalError","InternalError","RangeError","ReferenceError","SyntaxError","TypeError","URIError"],he=["setInterval","setTimeout","clearInterval","clearTimeout","require","exports","eval","isFinite","isNaN","parseFloat","parseInt","decodeURI","decodeURIComponent","encodeURI","encodeURIComponent","escape","unescape"],Ee=["arguments","this","super","console","window","document","localStorage","module","global"],we=[].concat(he,ve,fe)
;function ye(e){const n=e.regex,s=be,t={begin:/<[A-Za-z0-9\\._:-]+/,
end:/\/[A-Za-z0-9\\._:-]+>|\/>/,isTrulyOpeningTag:(e,n)=>{
const s=e[0].length+e.index,t=e.input[s]
;if("<"===t||","===t)return void n.ignoreMatch();let a
;">"===t&&(((e,{after:n})=>{const s="</"+e[0].slice(1)
;return-1!==e.input.indexOf(s,n)})(e,{after:s
})||n.ignoreMatch()),(a=e.input.substr(s).match(/^\s+extends\s+/))&&0===a.index&&n.ignoreMatch()
}},a={$pattern:be,keyword:ge,literal:_e,built_in:we,"variable.language":Ee
},r="\\.([0-9](_?[0-9])*)",i="0|[1-9](_?[0-9])*|0[0-7]*[89][0-9]*",o={
className:"number",variants:[{
begin:`(\\b(${i})((${r})|\\.)?|(${r}))[eE][+-]?([0-9](_?[0-9])*)\\b`},{
begin:`\\b(${i})\\b((${r})\\b|\\.)?|(${r})\\b`},{
begin:"\\b(0|[1-9](_?[0-9])*)n\\b"},{
begin:"\\b0[xX][0-9a-fA-F](_?[0-9a-fA-F])*n?\\b"},{
begin:"\\b0[bB][0-1](_?[0-1])*n?\\b"},{begin:"\\b0[oO][0-7](_?[0-7])*n?\\b"},{
begin:"\\b0[0-7]+n?\\b"}],relevance:0},c={className:"subst",begin:"\\$\\{",
end:"\\}",keywords:a,contains:[]},l={begin:"html`",end:"",starts:{end:"`",
returnEnd:!1,contains:[e.BACKSLASH_ESCAPE,c],subLanguage:"xml"}},d={
begin:"css`",end:"",starts:{end:"`",returnEnd:!1,
contains:[e.BACKSLASH_ESCAPE,c],subLanguage:"css"}},p={className:"string",
begin:"`",end:"`",contains:[e.BACKSLASH_ESCAPE,c]},m={className:"comment",
variants:[e.COMMENT(/\/\*\*(?!\/)/,"\\*/",{relevance:0,contains:[{
begin:"(?=@[A-Za-z]+)",relevance:0,contains:[{className:"doctag",
begin:"@[A-Za-z]+"},{className:"type",begin:"\\{",end:"\\}",excludeEnd:!0,
excludeBegin:!0,relevance:0},{className:"variable",begin:s+"(?=\\s*(-)|$)",
endsParent:!0,relevance:0},{begin:/(?=[^\n])\s/,relevance:0}]}]
}),e.C_BLOCK_COMMENT_MODE,e.C_LINE_COMMENT_MODE]
},u=[e.APOS_STRING_MODE,e.QUOTE_STRING_MODE,l,d,p,o];c.contains=u.concat({
begin:/\{/,end:/\}/,keywords:a,contains:["self"].concat(u)})
;const b=[].concat(m,c.contains),g=b.concat([{begin:/\(/,end:/\)/,keywords:a,
contains:["self"].concat(b)}]),_={className:"params",begin:/\(/,end:/\)/,
excludeBegin:!0,excludeEnd:!0,keywords:a,contains:g},v={variants:[{
match:[/class/,/\s+/,s,/\s+/,/extends/,/\s+/,n.concat(s,"(",n.concat(/\./,s),")*")],
scope:{1:"keyword",3:"title.class",5:"keyword",7:"title.class.inherited"}},{
match:[/class/,/\s+/,s],scope:{1:"keyword",3:"title.class"}}]},f={relevance:0,
match:n.either(/\bJSON/,/\b[A-Z][a-z]+([A-Z][a-z]*|\d)*/,/\b[A-Z]{2,}([A-Z][a-z]+|\d)+([A-Z][a-z]*)*/,/\b[A-Z]{2,}[a-z]+([A-Z][a-z]+|\d)*([A-Z][a-z]*)*/),
className:"title.class",keywords:{_:[...ve,...fe]}},h={variants:[{
match:[/function/,/\s+/,s,/(?=\s*\()/]},{match:[/function/,/\s*(?=\()/]}],
className:{1:"keyword",3:"title.function"},label:"func.def",contains:[_],
illegal:/%/},E={
match:n.concat(/\b/,(w=[...he,"super"],n.concat("(?!",w.join("|"),")")),s,n.lookahead(/\(/)),
className:"title.function",relevance:0};var w;const y={
begin:n.concat(/\./,n.lookahead(n.concat(s,/(?![0-9A-Za-z$_(])/))),end:s,
excludeBegin:!0,keywords:"prototype",className:"property",relevance:0},N={
match:[/get|set/,/\s+/,s,/(?=\()/],className:{1:"keyword",3:"title.function"},
contains:[{begin:/\(\)/},_]
},x="(\\([^()]*(\\([^()]*(\\([^()]*\\)[^()]*)*\\)[^()]*)*\\)|"+e.UNDERSCORE_IDENT_RE+")\\s*=>",k={
match:[/const|var|let/,/\s+/,s,/\s*/,/=\s*/,/(async\s*)?/,n.lookahead(x)],
keywords:"async",className:{1:"keyword",3:"title.function"},contains:[_]}
;return{name:"Javascript",aliases:["js","jsx","mjs","cjs"],keywords:a,exports:{
PARAMS_CONTAINS:g,CLASS_REFERENCE:f},illegal:/#(?![$_A-z])/,
contains:[e.SHEBANG({label:"shebang",binary:"node",relevance:5}),{
label:"use_strict",className:"meta",relevance:10,
begin:/^\s*['"]use (strict|asm)['"]/
},e.APOS_STRING_MODE,e.QUOTE_STRING_MODE,l,d,p,m,o,f,{className:"attr",
begin:s+n.lookahead(":"),relevance:0},k,{
begin:"("+e.RE_STARTERS_RE+"|\\b(case|return|throw)\\b)\\s*",
keywords:"return throw case",relevance:0,contains:[m,e.REGEXP_MODE,{
className:"function",begin:x,returnBegin:!0,end:"\\s*=>",contains:[{
className:"params",variants:[{begin:e.UNDERSCORE_IDENT_RE,relevance:0},{
className:null,begin:/\(\s*\)/,skip:!0},{begin:/\(/,end:/\)/,excludeBegin:!0,
excludeEnd:!0,keywords:a,contains:g}]}]},{begin:/,/,relevance:0},{match:/\s+/,
relevance:0},{variants:[{begin:"<>",end:"</>"},{
match:/<[A-Za-z0-9\\._:-]+\s*\/>/},{begin:t.begin,
"on:begin":t.isTrulyOpeningTag,end:t.end}],subLanguage:"xml",contains:[{
begin:t.begin,end:t.end,skip:!0,contains:["self"]}]}]},h,{
beginKeywords:"while if switch catch for"},{
begin:"\\b(?!function)"+e.UNDERSCORE_IDENT_RE+"\\([^()]*(\\([^()]*(\\([^()]*\\)[^()]*)*\\)[^()]*)*\\)\\s*\\{",
returnBegin:!0,label:"func.def",contains:[_,e.inherit(e.TITLE_MODE,{begin:s,
className:"title.function"})]},{match:/\.\.\./,relevance:0},y,{match:"\\$"+s,
relevance:0},{match:[/\bconstructor(?=\s*\()/],className:{1:"title.function"},
contains:[_]},E,{relevance:0,match:/\b[A-Z][A-Z_0-9]+\b/,
className:"variable.constant"},v,N,{match:/\$[(.]/}]}}
const Ne=e=>g(/\b/,e,/\w$/.test(e)?/\b/:/\B/),xe=["Protocol","Type"].map(Ne),ke=["init","self"].map(Ne),Oe=["Any","Self"],Me=["actor","associatedtype","async","await",/as\?/,/as!/,"as","break","case","catch","class","continue","convenience","default","defer","deinit","didSet","do","dynamic","else","enum","extension","fallthrough",/fileprivate\(set\)/,"fileprivate","final","for","func","get","guard","if","import","indirect","infix",/init\?/,/init!/,"inout",/internal\(set\)/,"internal","in","is","isolated","nonisolated","lazy","let","mutating","nonmutating",/open\(set\)/,"open","operator","optional","override","postfix","precedencegroup","prefix",/private\(set\)/,"private","protocol",/public\(set\)/,"public","repeat","required","rethrows","return","set","some","static","struct","subscript","super","switch","throws","throw",/try\?/,/try!/,"try","typealias",/unowned\(safe\)/,/unowned\(unsafe\)/,"unowned","var","weak","where","while","willSet"],Se=["false","nil","true"],Ce=["assignment","associativity","higherThan","left","lowerThan","none","right"],Ae=["#colorLiteral","#column","#dsohandle","#else","#elseif","#endif","#error","#file","#fileID","#fileLiteral","#filePath","#function","#if","#imageLiteral","#keyPath","#line","#selector","#sourceLocation","#warn_unqualified_access","#warning"],Te=["abs","all","any","assert","assertionFailure","debugPrint","dump","fatalError","getVaList","isKnownUniquelyReferenced","max","min","numericCast","pointwiseMax","pointwiseMin","precondition","preconditionFailure","print","readLine","repeatElement","sequence","stride","swap","swift_unboxFromSwiftValueWithType","transcode","type","unsafeBitCast","unsafeDowncast","withExtendedLifetime","withUnsafeMutablePointer","withUnsafePointer","withVaList","withoutActuallyEscaping","zip"],$e=_(/[/=\-+!*%<>&|^~?]/,/[\u00A1-\u00A7]/,/[\u00A9\u00AB]/,/[\u00AC\u00AE]/,/[\u00B0\u00B1]/,/[\u00B6\u00BB\u00BF\u00D7\u00F7]/,/[\u2016-\u2017]/,/[\u2020-\u2027]/,/[\u2030-\u203E]/,/[\u2041-\u2053]/,/[\u2055-\u205E]/,/[\u2190-\u23FF]/,/[\u2500-\u2775]/,/[\u2794-\u2BFF]/,/[\u2E00-\u2E7F]/,/[\u3001-\u3003]/,/[\u3008-\u3020]/,/[\u3030]/),qe=_($e,/[\u0300-\u036F]/,/[\u1DC0-\u1DFF]/,/[\u20D0-\u20FF]/,/[\uFE00-\uFE0F]/,/[\uFE20-\uFE2F]/),Re=g($e,qe,"*"),De=_(/[a-zA-Z_]/,/[\u00A8\u00AA\u00AD\u00AF\u00B2-\u00B5\u00B7-\u00BA]/,/[\u00BC-\u00BE\u00C0-\u00D6\u00D8-\u00F6\u00F8-\u00FF]/,/[\u0100-\u02FF\u0370-\u167F\u1681-\u180D\u180F-\u1DBF]/,/[\u1E00-\u1FFF]/,/[\u200B-\u200D\u202A-\u202E\u203F-\u2040\u2054\u2060-\u206F]/,/[\u2070-\u20CF\u2100-\u218F\u2460-\u24FF\u2776-\u2793]/,/[\u2C00-\u2DFF\u2E80-\u2FFF]/,/[\u3004-\u3007\u3021-\u302F\u3031-\u303F\u3040-\uD7FF]/,/[\uF900-\uFD3D\uFD40-\uFDCF\uFDF0-\uFE1F\uFE30-\uFE44]/,/[\uFE47-\uFEFE\uFF00-\uFFFD]/),Ie=_(De,/\d/,/[\u0300-\u036F\u1DC0-\u1DFF\u20D0-\u20FF\uFE20-\uFE2F]/),Le=g(De,Ie,"*"),Be=g(/[A-Z]/,Ie,"*"),ze=["autoclosure",g(/convention\(/,_("swift","block","c"),/\)/),"discardableResult","dynamicCallable","dynamicMemberLookup","escaping","frozen","GKInspectable","IBAction","IBDesignable","IBInspectable","IBOutlet","IBSegueAction","inlinable","main","nonobjc","NSApplicationMain","NSCopying","NSManaged",g(/objc\(/,Le,/\)/),"objc","objcMembers","propertyWrapper","requires_stored_property_inits","resultBuilder","testable","UIApplicationMain","unknown","usableFromInline"],Ue=["iOS","iOSApplicationExtension","macOS","macOSApplicationExtension","macCatalyst","macCatalystApplicationExtension","watchOS","watchOSApplicationExtension","tvOS","tvOSApplicationExtension","swift"]
;var Fe=Object.freeze({__proto__:null,grmr_bash:e=>{const n=e.regex,s={},t={
begin:/\$\{/,end:/\}/,contains:["self",{begin:/:-/,contains:[s]}]}
;Object.assign(s,{className:"variable",variants:[{
begin:n.concat(/\$[\w\d#@][\w\d_]*/,"(?![\\w\\d])(?![$])")},t]});const a={
className:"subst",begin:/\$\(/,end:/\)/,contains:[e.BACKSLASH_ESCAPE]},r={
begin:/<<-?\s*(?=\w+)/,starts:{contains:[e.END_SAME_AS_BEGIN({begin:/(\w+)/,
end:/(\w+)/,className:"string"})]}},i={className:"string",begin:/"/,end:/"/,
contains:[e.BACKSLASH_ESCAPE,s,a]};a.contains.push(i);const o={begin:/\$\(\(/,
end:/\)\)/,contains:[{begin:/\d+#[0-9a-f]+/,className:"number"},e.NUMBER_MODE,s]
},c=e.SHEBANG({binary:"(fish|bash|zsh|sh|csh|ksh|tcsh|dash|scsh)",relevance:10
}),l={className:"function",begin:/\w[\w\d_]*\s*\(\s*\)\s*\{/,returnBegin:!0,
contains:[e.inherit(e.TITLE_MODE,{begin:/\w[\w\d_]*/})],relevance:0};return{
name:"Bash",aliases:["sh"],keywords:{$pattern:/\b[a-z._-]+\b/,
keyword:["if","then","else","elif","fi","for","while","in","do","done","case","esac","function"],
literal:["true","false"],
built_in:["break","cd","continue","eval","exec","exit","export","getopts","hash","pwd","readonly","return","shift","test","times","trap","umask","unset","alias","bind","builtin","caller","command","declare","echo","enable","help","let","local","logout","mapfile","printf","read","readarray","source","type","typeset","ulimit","unalias","set","shopt","autoload","bg","bindkey","bye","cap","chdir","clone","comparguments","compcall","compctl","compdescribe","compfiles","compgroups","compquote","comptags","comptry","compvalues","dirs","disable","disown","echotc","echoti","emulate","fc","fg","float","functions","getcap","getln","history","integer","jobs","kill","limit","log","noglob","popd","print","pushd","pushln","rehash","sched","setcap","setopt","stat","suspend","ttyctl","unfunction","unhash","unlimit","unsetopt","vared","wait","whence","where","which","zcompile","zformat","zftp","zle","zmodload","zparseopts","zprof","zpty","zregexparse","zsocket","zstyle","ztcp","chcon","chgrp","chown","chmod","cp","dd","df","dir","dircolors","ln","ls","mkdir","mkfifo","mknod","mktemp","mv","realpath","rm","rmdir","shred","sync","touch","truncate","vdir","b2sum","base32","base64","cat","cksum","comm","csplit","cut","expand","fmt","fold","head","join","md5sum","nl","numfmt","od","paste","ptx","pr","sha1sum","sha224sum","sha256sum","sha384sum","sha512sum","shuf","sort","split","sum","tac","tail","tr","tsort","unexpand","uniq","wc","arch","basename","chroot","date","dirname","du","echo","env","expr","factor","groups","hostid","id","link","logname","nice","nohup","nproc","pathchk","pinky","printenv","printf","pwd","readlink","runcon","seq","sleep","stat","stdbuf","stty","tee","test","timeout","tty","uname","unlink","uptime","users","who","whoami","yes"]
},contains:[c,e.SHEBANG(),l,o,e.HASH_COMMENT_MODE,r,{match:/(\/[a-z._-]+)+/},i,{
className:"",begin:/\\"/},{className:"string",begin:/'/,end:/'/},s]}},
grmr_c:e=>{const n=e.regex,s=e.COMMENT("//","$",{contains:[{begin:/\\\n/}]
}),t="[a-zA-Z_]\\w*::",a="(decltype\\(auto\\)|"+n.optional(t)+"[a-zA-Z_]\\w*"+n.optional("<[^<>]+>")+")",r={
className:"type",variants:[{begin:"\\b[a-z\\d_]*_t\\b"},{
match:/\batomic_[a-z]{3,6}\b/}]},i={className:"string",variants:[{
begin:'(u8?|U|L)?"',end:'"',illegal:"\\n",contains:[e.BACKSLASH_ESCAPE]},{
begin:"(u8?|U|L)?'(\\\\(x[0-9A-Fa-f]{2}|u[0-9A-Fa-f]{4,8}|[0-7]{3}|\\S)|.)",
end:"'",illegal:"."},e.END_SAME_AS_BEGIN({
begin:/(?:u8?|U|L)?R"([^()\\ ]{0,16})\(/,end:/\)([^()\\ ]{0,16})"/})]},o={
className:"number",variants:[{begin:"\\b(0b[01']+)"},{
begin:"(-?)\\b([\\d']+(\\.[\\d']*)?|\\.[\\d']+)((ll|LL|l|L)(u|U)?|(u|U)(ll|LL|l|L)?|f|F|b|B)"
},{
begin:"(-?)(\\b0[xX][a-fA-F0-9']+|(\\b[\\d']+(\\.[\\d']*)?|\\.[\\d']+)([eE][-+]?[\\d']+)?)"
}],relevance:0},c={className:"meta",begin:/#\s*[a-z]+\b/,end:/$/,keywords:{
keyword:"if else elif endif define undef warning error line pragma _Pragma ifdef ifndef include"
},contains:[{begin:/\\\n/,relevance:0},e.inherit(i,{className:"string"}),{
className:"string",begin:/<.*?>/},s,e.C_BLOCK_COMMENT_MODE]},l={
className:"title",begin:n.optional(t)+e.IDENT_RE,relevance:0
},d=n.optional(t)+e.IDENT_RE+"\\s*\\(",p={
keyword:["asm","auto","break","case","continue","default","do","else","enum","extern","for","fortran","goto","if","inline","register","restrict","return","sizeof","struct","switch","typedef","union","volatile","while","_Alignas","_Alignof","_Atomic","_Generic","_Noreturn","_Static_assert","_Thread_local","alignas","alignof","noreturn","static_assert","thread_local","_Pragma"],
type:["float","double","signed","unsigned","int","short","long","char","void","_Bool","_Complex","_Imaginary","_Decimal32","_Decimal64","_Decimal128","const","static","complex","bool","imaginary"],
literal:"true false NULL",
built_in:"std string wstring cin cout cerr clog stdin stdout stderr stringstream istringstream ostringstream auto_ptr deque list queue stack vector map set pair bitset multiset multimap unordered_set unordered_map unordered_multiset unordered_multimap priority_queue make_pair array shared_ptr abort terminate abs acos asin atan2 atan calloc ceil cosh cos exit exp fabs floor fmod fprintf fputs free frexp fscanf future isalnum isalpha iscntrl isdigit isgraph islower isprint ispunct isspace isupper isxdigit tolower toupper labs ldexp log10 log malloc realloc memchr memcmp memcpy memset modf pow printf putchar puts scanf sinh sin snprintf sprintf sqrt sscanf strcat strchr strcmp strcpy strcspn strlen strncat strncmp strncpy strpbrk strrchr strspn strstr tanh tan vfprintf vprintf vsprintf endl initializer_list unique_ptr"
},m=[c,r,s,e.C_BLOCK_COMMENT_MODE,o,i],u={variants:[{begin:/=/,end:/;/},{
begin:/\(/,end:/\)/},{beginKeywords:"new throw return else",end:/;/}],
keywords:p,contains:m.concat([{begin:/\(/,end:/\)/,keywords:p,
contains:m.concat(["self"]),relevance:0}]),relevance:0},b={
begin:"("+a+"[\\*&\\s]+)+"+d,returnBegin:!0,end:/[{;=]/,excludeEnd:!0,
keywords:p,illegal:/[^\w\s\*&:<>.]/,contains:[{begin:"decltype\\(auto\\)",
keywords:p,relevance:0},{begin:d,returnBegin:!0,contains:[e.inherit(l,{
className:"title.function"})],relevance:0},{relevance:0,match:/,/},{
className:"params",begin:/\(/,end:/\)/,keywords:p,relevance:0,
contains:[s,e.C_BLOCK_COMMENT_MODE,i,o,r,{begin:/\(/,end:/\)/,keywords:p,
relevance:0,contains:["self",s,e.C_BLOCK_COMMENT_MODE,i,o,r]}]
},r,s,e.C_BLOCK_COMMENT_MODE,c]};return{name:"C",aliases:["h"],keywords:p,
disableAutodetect:!0,illegal:"</",contains:[].concat(u,b,m,[c,{
begin:e.IDENT_RE+"::",keywords:p},{className:"class",
beginKeywords:"enum class struct union",end:/[{;:<>=]/,contains:[{
beginKeywords:"final class struct"},e.TITLE_MODE]}]),exports:{preprocessor:c,
strings:i,keywords:p}}},grmr_cpp:e=>{const n=e.regex,s=e.COMMENT("//","$",{
contains:[{begin:/\\\n/}]
}),t="[a-zA-Z_]\\w*::",a="(?!struct)(decltype\\(auto\\)|"+n.optional(t)+"[a-zA-Z_]\\w*"+n.optional("<[^<>]+>")+")",r={
className:"type",begin:"\\b[a-z\\d_]*_t\\b"},i={className:"string",variants:[{
begin:'(u8?|U|L)?"',end:'"',illegal:"\\n",contains:[e.BACKSLASH_ESCAPE]},{
begin:"(u8?|U|L)?'(\\\\(x[0-9A-Fa-f]{2}|u[0-9A-Fa-f]{4,8}|[0-7]{3}|\\S)|.)",
end:"'",illegal:"."},e.END_SAME_AS_BEGIN({
begin:/(?:u8?|U|L)?R"([^()\\ ]{0,16})\(/,end:/\)([^()\\ ]{0,16})"/})]},o={
className:"number",variants:[{begin:"\\b(0b[01']+)"},{
begin:"(-?)\\b([\\d']+(\\.[\\d']*)?|\\.[\\d']+)((ll|LL|l|L)(u|U)?|(u|U)(ll|LL|l|L)?|f|F|b|B)"
},{
begin:"(-?)(\\b0[xX][a-fA-F0-9']+|(\\b[\\d']+(\\.[\\d']*)?|\\.[\\d']+)([eE][-+]?[\\d']+)?)"
}],relevance:0},c={className:"meta",begin:/#\s*[a-z]+\b/,end:/$/,keywords:{
keyword:"if else elif endif define undef warning error line pragma _Pragma ifdef ifndef include"
},contains:[{begin:/\\\n/,relevance:0},e.inherit(i,{className:"string"}),{
className:"string",begin:/<.*?>/},s,e.C_BLOCK_COMMENT_MODE]},l={
className:"title",begin:n.optional(t)+e.IDENT_RE,relevance:0
},d=n.optional(t)+e.IDENT_RE+"\\s*\\(",p={
type:["bool","char","char16_t","char32_t","char8_t","double","float","int","long","short","void","wchar_t","unsigned","signed","const","static"],
keyword:["alignas","alignof","and","and_eq","asm","atomic_cancel","atomic_commit","atomic_noexcept","auto","bitand","bitor","break","case","catch","class","co_await","co_return","co_yield","compl","concept","const_cast|10","consteval","constexpr","constinit","continue","decltype","default","delete","do","dynamic_cast|10","else","enum","explicit","export","extern","false","final","for","friend","goto","if","import","inline","module","mutable","namespace","new","noexcept","not","not_eq","nullptr","operator","or","or_eq","override","private","protected","public","reflexpr","register","reinterpret_cast|10","requires","return","sizeof","static_assert","static_cast|10","struct","switch","synchronized","template","this","thread_local","throw","transaction_safe","transaction_safe_dynamic","true","try","typedef","typeid","typename","union","using","virtual","volatile","while","xor","xor_eq"],
literal:["NULL","false","nullopt","nullptr","true"],built_in:["_Pragma"],
_type_hints:["any","auto_ptr","barrier","binary_semaphore","bitset","complex","condition_variable","condition_variable_any","counting_semaphore","deque","false_type","future","imaginary","initializer_list","istringstream","jthread","latch","lock_guard","multimap","multiset","mutex","optional","ostringstream","packaged_task","pair","promise","priority_queue","queue","recursive_mutex","recursive_timed_mutex","scoped_lock","set","shared_future","shared_lock","shared_mutex","shared_timed_mutex","shared_ptr","stack","string_view","stringstream","timed_mutex","thread","true_type","tuple","unique_lock","unique_ptr","unordered_map","unordered_multimap","unordered_multiset","unordered_set","variant","vector","weak_ptr","wstring","wstring_view"]
},m={className:"function.dispatch",relevance:0,keywords:{
_hint:["abort","abs","acos","apply","as_const","asin","atan","atan2","calloc","ceil","cerr","cin","clog","cos","cosh","cout","declval","endl","exchange","exit","exp","fabs","floor","fmod","forward","fprintf","fputs","free","frexp","fscanf","future","invoke","isalnum","isalpha","iscntrl","isdigit","isgraph","islower","isprint","ispunct","isspace","isupper","isxdigit","labs","launder","ldexp","log","log10","make_pair","make_shared","make_shared_for_overwrite","make_tuple","make_unique","malloc","memchr","memcmp","memcpy","memset","modf","move","pow","printf","putchar","puts","realloc","scanf","sin","sinh","snprintf","sprintf","sqrt","sscanf","std","stderr","stdin","stdout","strcat","strchr","strcmp","strcpy","strcspn","strlen","strncat","strncmp","strncpy","strpbrk","strrchr","strspn","strstr","swap","tan","tanh","terminate","to_underlying","tolower","toupper","vfprintf","visit","vprintf","vsprintf"]
},
begin:n.concat(/\b/,/(?!decltype)/,/(?!if)/,/(?!for)/,/(?!switch)/,/(?!while)/,e.IDENT_RE,n.lookahead(/(<[^<>]+>|)\s*\(/))
},u=[m,c,r,s,e.C_BLOCK_COMMENT_MODE,o,i],b={variants:[{begin:/=/,end:/;/},{
begin:/\(/,end:/\)/},{beginKeywords:"new throw return else",end:/;/}],
keywords:p,contains:u.concat([{begin:/\(/,end:/\)/,keywords:p,
contains:u.concat(["self"]),relevance:0}]),relevance:0},g={className:"function",
begin:"("+a+"[\\*&\\s]+)+"+d,returnBegin:!0,end:/[{;=]/,excludeEnd:!0,
keywords:p,illegal:/[^\w\s\*&:<>.]/,contains:[{begin:"decltype\\(auto\\)",
keywords:p,relevance:0},{begin:d,returnBegin:!0,contains:[l],relevance:0},{
begin:/::/,relevance:0},{begin:/:/,endsWithParent:!0,contains:[i,o]},{
relevance:0,match:/,/},{className:"params",begin:/\(/,end:/\)/,keywords:p,
relevance:0,contains:[s,e.C_BLOCK_COMMENT_MODE,i,o,r,{begin:/\(/,end:/\)/,
keywords:p,relevance:0,contains:["self",s,e.C_BLOCK_COMMENT_MODE,i,o,r]}]
},r,s,e.C_BLOCK_COMMENT_MODE,c]};return{name:"C++",
aliases:["cc","c++","h++","hpp","hh","hxx","cxx"],keywords:p,illegal:"</",
classNameAliases:{"function.dispatch":"built_in"},
contains:[].concat(b,g,m,u,[c,{
begin:"\\b(deque|list|queue|priority_queue|pair|stack|vector|map|set|bitset|multiset|multimap|unordered_map|unordered_set|unordered_multiset|unordered_multimap|array|tuple|optional|variant|function)\\s*<(?!<)",
end:">",keywords:p,contains:["self",r]},{begin:e.IDENT_RE+"::",keywords:p},{
match:[/\b(?:enum(?:\s+(?:class|struct))?|class|struct|union)/,/\s+/,/\w+/],
className:{1:"keyword",3:"title.class"}}])}},grmr_csharp:e=>{const n={
keyword:["abstract","as","base","break","case","catch","class","const","continue","do","else","event","explicit","extern","finally","fixed","for","foreach","goto","if","implicit","in","interface","internal","is","lock","namespace","new","operator","out","override","params","private","protected","public","readonly","record","ref","return","sealed","sizeof","stackalloc","static","struct","switch","this","throw","try","typeof","unchecked","unsafe","using","virtual","void","volatile","while"].concat(["add","alias","and","ascending","async","await","by","descending","equals","from","get","global","group","init","into","join","let","nameof","not","notnull","on","or","orderby","partial","remove","select","set","unmanaged","value|0","var","when","where","with","yield"]),
built_in:["bool","byte","char","decimal","delegate","double","dynamic","enum","float","int","long","nint","nuint","object","sbyte","short","string","ulong","uint","ushort"],
literal:["default","false","null","true"]},s=e.inherit(e.TITLE_MODE,{
begin:"[a-zA-Z](\\.?\\w)*"}),t={className:"number",variants:[{
begin:"\\b(0b[01']+)"},{
begin:"(-?)\\b([\\d']+(\\.[\\d']*)?|\\.[\\d']+)(u|U|l|L|ul|UL|f|F|b|B)"},{
begin:"(-?)(\\b0[xX][a-fA-F0-9']+|(\\b[\\d']+(\\.[\\d']*)?|\\.[\\d']+)([eE][-+]?[\\d']+)?)"
}],relevance:0},a={className:"string",begin:'@"',end:'"',contains:[{begin:'""'}]
},r=e.inherit(a,{illegal:/\n/}),i={className:"subst",begin:/\{/,end:/\}/,
keywords:n},o=e.inherit(i,{illegal:/\n/}),c={className:"string",begin:/\$"/,
end:'"',illegal:/\n/,contains:[{begin:/\{\{/},{begin:/\}\}/
},e.BACKSLASH_ESCAPE,o]},l={className:"string",begin:/\$@"/,end:'"',contains:[{
begin:/\{\{/},{begin:/\}\}/},{begin:'""'},i]},d=e.inherit(l,{illegal:/\n/,
contains:[{begin:/\{\{/},{begin:/\}\}/},{begin:'""'},o]})
;i.contains=[l,c,a,e.APOS_STRING_MODE,e.QUOTE_STRING_MODE,t,e.C_BLOCK_COMMENT_MODE],
o.contains=[d,c,r,e.APOS_STRING_MODE,e.QUOTE_STRING_MODE,t,e.inherit(e.C_BLOCK_COMMENT_MODE,{
illegal:/\n/})];const p={variants:[l,c,a,e.APOS_STRING_MODE,e.QUOTE_STRING_MODE]
},m={begin:"<",end:">",contains:[{beginKeywords:"in out"},s]
},u=e.IDENT_RE+"(<"+e.IDENT_RE+"(\\s*,\\s*"+e.IDENT_RE+")*>)?(\\[\\])?",b={
begin:"@"+e.IDENT_RE,relevance:0};return{name:"C#",aliases:["cs","c#"],
keywords:n,illegal:/::/,contains:[e.COMMENT("///","$",{returnBegin:!0,
contains:[{className:"doctag",variants:[{begin:"///",relevance:0},{
begin:"\x3c!--|--\x3e"},{begin:"</?",end:">"}]}]
}),e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE,{className:"meta",begin:"#",
end:"$",keywords:{
keyword:"if else elif endif define undef warning error line region endregion pragma checksum"
}},p,t,{beginKeywords:"class interface",relevance:0,end:/[{;=]/,
illegal:/[^\s:,]/,contains:[{beginKeywords:"where class"
},s,m,e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE]},{beginKeywords:"namespace",
relevance:0,end:/[{;=]/,illegal:/[^\s:]/,
contains:[s,e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE]},{
beginKeywords:"record",relevance:0,end:/[{;=]/,illegal:/[^\s:]/,
contains:[s,m,e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE]},{className:"meta",
begin:"^\\s*\\[(?=[\\w])",excludeBegin:!0,end:"\\]",excludeEnd:!0,contains:[{
className:"string",begin:/"/,end:/"/}]},{
beginKeywords:"new return throw await else",relevance:0},{className:"function",
begin:"("+u+"\\s+)+"+e.IDENT_RE+"\\s*(<[^=]+>\\s*)?\\(",returnBegin:!0,
end:/\s*[{;=]/,excludeEnd:!0,keywords:n,contains:[{
beginKeywords:"public private protected static internal protected abstract async extern override unsafe virtual new sealed partial",
relevance:0},{begin:e.IDENT_RE+"\\s*(<[^=]+>\\s*)?\\(",returnBegin:!0,
contains:[e.TITLE_MODE,m],relevance:0},{match:/\(\)/},{className:"params",
begin:/\(/,end:/\)/,excludeBegin:!0,excludeEnd:!0,keywords:n,relevance:0,
contains:[p,t,e.C_BLOCK_COMMENT_MODE]
},e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE]},b]}},grmr_css:e=>{
const n=e.regex,s=te(e),t=[e.APOS_STRING_MODE,e.QUOTE_STRING_MODE];return{
name:"CSS",case_insensitive:!0,illegal:/[=|'\$]/,keywords:{
keyframePosition:"from to"},classNameAliases:{keyframePosition:"selector-tag"},
contains:[s.BLOCK_COMMENT,{begin:/-(webkit|moz|ms|o)-(?=[a-z])/
},s.CSS_NUMBER_MODE,{className:"selector-id",begin:/#[A-Za-z0-9_-]+/,relevance:0
},{className:"selector-class",begin:"\\.[a-zA-Z-][a-zA-Z0-9_-]*",relevance:0
},s.ATTRIBUTE_SELECTOR_MODE,{className:"selector-pseudo",variants:[{
begin:":("+ie.join("|")+")"},{begin:":(:)?("+oe.join("|")+")"}]
},s.CSS_VARIABLE,{className:"attribute",begin:"\\b("+ce.join("|")+")\\b"},{
begin:/:/,end:/[;}{]/,
contains:[s.BLOCK_COMMENT,s.HEXCOLOR,s.IMPORTANT,s.CSS_NUMBER_MODE,...t,{
begin:/(url|data-uri)\(/,end:/\)/,relevance:0,keywords:{built_in:"url data-uri"
},contains:[{className:"string",begin:/[^)]/,endsWithParent:!0,excludeEnd:!0}]
},s.FUNCTION_DISPATCH]},{begin:n.lookahead(/@/),end:"[{;]",relevance:0,
illegal:/:/,contains:[{className:"keyword",begin:/@-?\w[\w]*(-\w+)*/},{
begin:/\s/,endsWithParent:!0,excludeEnd:!0,relevance:0,keywords:{
$pattern:/[a-z-]+/,keyword:"and or not only",attribute:re.join(" ")},contains:[{
begin:/[a-z-]+(?=:)/,className:"attribute"},...t,s.CSS_NUMBER_MODE]}]},{
className:"selector-tag",begin:"\\b("+ae.join("|")+")\\b"}]}},grmr_diff:e=>{
const n=e.regex;return{name:"Diff",aliases:["patch"],contains:[{
className:"meta",relevance:10,
match:n.either(/^@@ +-\d+,\d+ +\+\d+,\d+ +@@/,/^\*\*\* +\d+,\d+ +\*\*\*\*$/,/^--- +\d+,\d+ +----$/)
},{className:"comment",variants:[{
begin:n.either(/Index: /,/^index/,/={3,}/,/^-{3}/,/^\*{3} /,/^\+{3}/,/^diff --git/),
end:/$/},{match:/^\*{15}$/}]},{className:"addition",begin:/^\+/,end:/$/},{
className:"deletion",begin:/^-/,end:/$/},{className:"addition",begin:/^!/,
end:/$/}]}},grmr_go:e=>{const n={
keyword:["break","case","chan","const","continue","default","defer","else","fallthrough","for","func","go","goto","if","import","interface","map","package","range","return","select","struct","switch","type","var"],
type:["bool","byte","complex64","complex128","error","float32","float64","int8","int16","int32","int64","string","uint8","uint16","uint32","uint64","int","uint","uintptr","rune"],
literal:["true","false","iota","nil"],
built_in:["append","cap","close","complex","copy","imag","len","make","new","panic","print","println","real","recover","delete"]
};return{name:"Go",aliases:["golang"],keywords:n,illegal:"</",
contains:[e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE,{className:"string",
variants:[e.QUOTE_STRING_MODE,e.APOS_STRING_MODE,{begin:"`",end:"`"}]},{
className:"number",variants:[{begin:e.C_NUMBER_RE+"[i]",relevance:1
},e.C_NUMBER_MODE]},{begin:/:=/},{className:"function",beginKeywords:"func",
end:"\\s*(\\{|$)",excludeEnd:!0,contains:[e.TITLE_MODE,{className:"params",
begin:/\(/,end:/\)/,endsParent:!0,keywords:n,illegal:/["']/}]}]}},grmr_ini:e=>{
const n=e.regex,s={className:"number",relevance:0,variants:[{
begin:/([+-]+)?[\d]+_[\d_]+/},{begin:e.NUMBER_RE}]},t=e.COMMENT();t.variants=[{
begin:/;/,end:/$/},{begin:/#/,end:/$/}];const a={className:"variable",
variants:[{begin:/\$[\w\d"][\w\d_]*/},{begin:/\$\{(.*?)\}/}]},r={
className:"literal",begin:/\bon|off|true|false|yes|no\b/},i={className:"string",
contains:[e.BACKSLASH_ESCAPE],variants:[{begin:"'''",end:"'''",relevance:10},{
begin:'"""',end:'"""',relevance:10},{begin:'"',end:'"'},{begin:"'",end:"'"}]
},o={begin:/\[/,end:/\]/,contains:[t,r,a,i,s,"self"],relevance:0
},c=n.either(/[A-Za-z0-9_-]+/,/"(\\"|[^"])*"/,/'[^']*'/);return{
name:"TOML, also INI",aliases:["toml"],case_insensitive:!0,illegal:/\S/,
contains:[t,{className:"section",begin:/\[+/,end:/\]+/},{
begin:n.concat(c,"(\\s*\\.\\s*",c,")*",n.lookahead(/\s*=\s*[^#\s]/)),
className:"attr",starts:{end:/$/,contains:[t,o,r,a,i,s]}}]}},grmr_java:e=>{
e.regex
;const n="[\xc0-\u02b8a-zA-Z_$][\xc0-\u02b8a-zA-Z_$0-9]*",s=n+ue("(?:<"+n+"~~~(?:\\s*,\\s*"+n+"~~~)*>)?",/~~~/g,2),t={
keyword:["synchronized","abstract","private","var","static","if","const ","for","while","strictfp","finally","protected","import","native","final","void","enum","else","break","transient","catch","instanceof","volatile","case","assert","package","default","public","try","switch","continue","throws","protected","public","private","module","requires","exports","do","sealed"],
literal:["false","true","null"],
type:["char","boolean","long","float","int","byte","short","double"],
built_in:["super","this"]},a={className:"meta",begin:"@"+n,contains:[{
begin:/\(/,end:/\)/,contains:["self"]}]},r={className:"params",begin:/\(/,
end:/\)/,keywords:t,relevance:0,contains:[e.C_BLOCK_COMMENT_MODE],endsParent:!0}
;return{name:"Java",aliases:["jsp"],keywords:t,illegal:/<\/|#/,
contains:[e.COMMENT("/\\*\\*","\\*/",{relevance:0,contains:[{begin:/\w+@/,
relevance:0},{className:"doctag",begin:"@[A-Za-z]+"}]}),{
begin:/import java\.[a-z]+\./,keywords:"import",relevance:2
},e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE,{begin:/"""/,end:/"""/,
className:"string",contains:[e.BACKSLASH_ESCAPE]
},e.APOS_STRING_MODE,e.QUOTE_STRING_MODE,{
match:[/\b(?:class|interface|enum|extends|implements|new)/,/\s+/,n],className:{
1:"keyword",3:"title.class"}},{match:/non-sealed/,scope:"keyword"},{
begin:[n,/\s+/,n,/\s+/,/=/],className:{1:"type",3:"variable",5:"operator"}},{
begin:[/record/,/\s+/,n],className:{1:"keyword",3:"title.class"},
contains:[r,e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE]},{
beginKeywords:"new throw return else",relevance:0},{
begin:["(?:"+s+"\\s+)",e.UNDERSCORE_IDENT_RE,/\s*(?=\()/],className:{
2:"title.function"},keywords:t,contains:[{className:"params",begin:/\(/,
end:/\)/,keywords:t,relevance:0,
contains:[a,e.APOS_STRING_MODE,e.QUOTE_STRING_MODE,me,e.C_BLOCK_COMMENT_MODE]
},e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE]},me,a]}},grmr_javascript:ye,
grmr_json:e=>({name:"JSON",contains:[{className:"attr",
begin:/"(\\.|[^\\"\r\n])*"(?=\s*:)/,relevance:1.01},{match:/[{}[\],:]/,
className:"punctuation",relevance:0},e.QUOTE_STRING_MODE,{
beginKeywords:"true false null"
},e.C_NUMBER_MODE,e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE],illegal:"\\S"}),
grmr_kotlin:e=>{const n={
keyword:"abstract as val var vararg get set class object open private protected public noinline crossinline dynamic final enum if else do while for when throw try catch finally import package is in fun override companion reified inline lateinit init interface annotation data sealed internal infix operator out by constructor super tailrec where const inner suspend typealias external expect actual",
built_in:"Byte Short Char Int Long Boolean Float Double Void Unit Nothing",
literal:"true false null"},s={className:"symbol",begin:e.UNDERSCORE_IDENT_RE+"@"
},t={className:"subst",begin:/\$\{/,end:/\}/,contains:[e.C_NUMBER_MODE]},a={
className:"variable",begin:"\\$"+e.UNDERSCORE_IDENT_RE},r={className:"string",
variants:[{begin:'"""',end:'"""(?=[^"])',contains:[a,t]},{begin:"'",end:"'",
illegal:/\n/,contains:[e.BACKSLASH_ESCAPE]},{begin:'"',end:'"',illegal:/\n/,
contains:[e.BACKSLASH_ESCAPE,a,t]}]};t.contains.push(r);const i={
className:"meta",
begin:"@(?:file|property|field|get|set|receiver|param|setparam|delegate)\\s*:(?:\\s*"+e.UNDERSCORE_IDENT_RE+")?"
},o={className:"meta",begin:"@"+e.UNDERSCORE_IDENT_RE,contains:[{begin:/\(/,
end:/\)/,contains:[e.inherit(r,{className:"string"})]}]
},c=me,l=e.COMMENT("/\\*","\\*/",{contains:[e.C_BLOCK_COMMENT_MODE]}),d={
variants:[{className:"type",begin:e.UNDERSCORE_IDENT_RE},{begin:/\(/,end:/\)/,
contains:[]}]},p=d;return p.variants[1].contains=[d],d.variants[1].contains=[p],
{name:"Kotlin",aliases:["kt","kts"],keywords:n,
contains:[e.COMMENT("/\\*\\*","\\*/",{relevance:0,contains:[{className:"doctag",
begin:"@[A-Za-z]+"}]}),e.C_LINE_COMMENT_MODE,l,{className:"keyword",
begin:/\b(break|continue|return|this)\b/,starts:{contains:[{className:"symbol",
begin:/@\w+/}]}},s,i,o,{className:"function",beginKeywords:"fun",end:"[(]|$",
returnBegin:!0,excludeEnd:!0,keywords:n,relevance:5,contains:[{
begin:e.UNDERSCORE_IDENT_RE+"\\s*\\(",returnBegin:!0,relevance:0,
contains:[e.UNDERSCORE_TITLE_MODE]},{className:"type",begin:/</,end:/>/,
keywords:"reified",relevance:0},{className:"params",begin:/\(/,end:/\)/,
endsParent:!0,keywords:n,relevance:0,contains:[{begin:/:/,end:/[=,\/]/,
endsWithParent:!0,contains:[d,e.C_LINE_COMMENT_MODE,l],relevance:0
},e.C_LINE_COMMENT_MODE,l,i,o,r,e.C_NUMBER_MODE]},l]},{className:"class",
beginKeywords:"class interface trait",end:/[:\{(]|$/,excludeEnd:!0,
illegal:"extends implements",contains:[{
beginKeywords:"public protected internal private constructor"
},e.UNDERSCORE_TITLE_MODE,{className:"type",begin:/</,end:/>/,excludeBegin:!0,
excludeEnd:!0,relevance:0},{className:"type",begin:/[,:]\s*/,end:/[<\(,]|$/,
excludeBegin:!0,returnEnd:!0},i,o]},r,{className:"meta",begin:"^#!/usr/bin/env",
end:"$",illegal:"\n"},c]}},grmr_less:e=>{
const n=te(e),s=le,t="([\\w-]+|@\\{[\\w-]+\\})",a=[],r=[],i=e=>({
className:"string",begin:"~?"+e+".*?"+e}),o=(e,n,s)=>({className:e,begin:n,
relevance:s}),c={$pattern:/[a-z-]+/,keyword:"and or not only",
attribute:re.join(" ")},l={begin:"\\(",end:"\\)",contains:r,keywords:c,
relevance:0}
;r.push(e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE,i("'"),i('"'),n.CSS_NUMBER_MODE,{
begin:"(url|data-uri)\\(",starts:{className:"string",end:"[\\)\\n]",
excludeEnd:!0}
},n.HEXCOLOR,l,o("variable","@@?[\\w-]+",10),o("variable","@\\{[\\w-]+\\}"),o("built_in","~?`[^`]*?`"),{
className:"attribute",begin:"[\\w-]+\\s*:",end:":",returnBegin:!0,excludeEnd:!0
},n.IMPORTANT);const d=r.concat({begin:/\{/,end:/\}/,contains:a}),p={
beginKeywords:"when",endsWithParent:!0,contains:[{beginKeywords:"and not"
}].concat(r)},m={begin:t+"\\s*:",returnBegin:!0,end:/[;}]/,relevance:0,
contains:[{begin:/-(webkit|moz|ms|o)-/},n.CSS_VARIABLE,{className:"attribute",
begin:"\\b("+ce.join("|")+")\\b",end:/(?=:)/,starts:{endsWithParent:!0,
illegal:"[<=$]",relevance:0,contains:r}}]},u={className:"keyword",
begin:"@(import|media|charset|font-face|(-[a-z]+-)?keyframes|supports|document|namespace|page|viewport|host)\\b",
starts:{end:"[;{}]",keywords:c,returnEnd:!0,contains:r,relevance:0}},b={
className:"variable",variants:[{begin:"@[\\w-]+\\s*:",relevance:15},{
begin:"@[\\w-]+"}],starts:{end:"[;}]",returnEnd:!0,contains:d}},g={variants:[{
begin:"[\\.#:&\\[>]",end:"[;{}]"},{begin:t,end:/\{/}],returnBegin:!0,
returnEnd:!0,illegal:"[<='$\"]",relevance:0,
contains:[e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE,p,o("keyword","all\\b"),o("variable","@\\{[\\w-]+\\}"),{
begin:"\\b("+ae.join("|")+")\\b",className:"selector-tag"
},n.CSS_NUMBER_MODE,o("selector-tag",t,0),o("selector-id","#"+t),o("selector-class","\\."+t,0),o("selector-tag","&",0),n.ATTRIBUTE_SELECTOR_MODE,{
className:"selector-pseudo",begin:":("+ie.join("|")+")"},{
className:"selector-pseudo",begin:":(:)?("+oe.join("|")+")"},{begin:/\(/,
end:/\)/,relevance:0,contains:d},{begin:"!important"},n.FUNCTION_DISPATCH]},_={
begin:`[\\w-]+:(:)?(${s.join("|")})`,returnBegin:!0,contains:[g]}
;return a.push(e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE,u,b,_,m,g),{
name:"Less",case_insensitive:!0,illegal:"[=>'/<($\"]",contains:a}},grmr_lua:e=>{
const n="\\[=*\\[",s="\\]=*\\]",t={begin:n,end:s,contains:["self"]
},a=[e.COMMENT("--(?!\\[=*\\[)","$"),e.COMMENT("--\\[=*\\[",s,{contains:[t],
relevance:10})];return{name:"Lua",keywords:{$pattern:e.UNDERSCORE_IDENT_RE,
literal:"true false nil",
keyword:"and break do else elseif end for goto if in local not or repeat return then until while",
built_in:"_G _ENV _VERSION __index __newindex __mode __call __metatable __tostring __len __gc __add __sub __mul __div __mod __pow __concat __unm __eq __lt __le assert collectgarbage dofile error getfenv getmetatable ipairs load loadfile loadstring module next pairs pcall print rawequal rawget rawset require select setfenv setmetatable tonumber tostring type unpack xpcall arg self coroutine resume yield status wrap create running debug getupvalue debug sethook getmetatable gethook setmetatable setlocal traceback setfenv getinfo setupvalue getlocal getregistry getfenv io lines write close flush open output type read stderr stdin input stdout popen tmpfile math log max acos huge ldexp pi cos tanh pow deg tan cosh sinh random randomseed frexp ceil floor rad abs sqrt modf asin min mod fmod log10 atan2 exp sin atan os exit setlocale date getenv difftime remove time clock tmpname rename execute package preload loadlib loaded loaders cpath config path seeall string sub upper len gfind rep find match char dump gmatch reverse byte format gsub lower table setn insert getn foreachi maxn foreach concat sort remove"
},contains:a.concat([{className:"function",beginKeywords:"function",end:"\\)",
contains:[e.inherit(e.TITLE_MODE,{
begin:"([_a-zA-Z]\\w*\\.)*([_a-zA-Z]\\w*:)?[_a-zA-Z]\\w*"}),{className:"params",
begin:"\\(",endsWithParent:!0,contains:a}].concat(a)
},e.C_NUMBER_MODE,e.APOS_STRING_MODE,e.QUOTE_STRING_MODE,{className:"string",
begin:n,end:s,contains:[t],relevance:5}])}},grmr_makefile:e=>{const n={
className:"variable",variants:[{begin:"\\$\\("+e.UNDERSCORE_IDENT_RE+"\\)",
contains:[e.BACKSLASH_ESCAPE]},{begin:/\$[@%<?\^\+\*]/}]},s={className:"string",
begin:/"/,end:/"/,contains:[e.BACKSLASH_ESCAPE,n]},t={className:"variable",
begin:/\$\([\w-]+\s/,end:/\)/,keywords:{
built_in:"subst patsubst strip findstring filter filter-out sort word wordlist firstword lastword dir notdir suffix basename addsuffix addprefix join wildcard realpath abspath error warning shell origin flavor foreach if or and call eval file value"
},contains:[n]},a={begin:"^"+e.UNDERSCORE_IDENT_RE+"\\s*(?=[:+?]?=)"},r={
className:"section",begin:/^[^\s]+:/,end:/$/,contains:[n]};return{
name:"Makefile",aliases:["mk","mak","make"],keywords:{$pattern:/[\w-]+/,
keyword:"define endef undefine ifdef ifndef ifeq ifneq else endif include -include sinclude override export unexport private vpath"
},contains:[e.HASH_COMMENT_MODE,n,s,t,a,{className:"meta",begin:/^\.PHONY:/,
end:/$/,keywords:{$pattern:/[\.\w]+/,keyword:".PHONY"}},r]}},grmr_xml:e=>{
const n=e.regex,s=n.concat(/[A-Z_]/,n.optional(/[A-Z0-9_.-]*:/),/[A-Z0-9_.-]*/),t={
className:"symbol",begin:/&[a-z]+;|&#[0-9]+;|&#x[a-f0-9]+;/},a={begin:/\s/,
contains:[{className:"keyword",begin:/#?[a-z_][a-z1-9_-]+/,illegal:/\n/}]
},r=e.inherit(a,{begin:/\(/,end:/\)/}),i=e.inherit(e.APOS_STRING_MODE,{
className:"string"}),o=e.inherit(e.QUOTE_STRING_MODE,{className:"string"}),c={
endsWithParent:!0,illegal:/</,relevance:0,contains:[{className:"attr",
begin:/[A-Za-z0-9._:-]+/,relevance:0},{begin:/=\s*/,relevance:0,contains:[{
className:"string",endsParent:!0,variants:[{begin:/"/,end:/"/,contains:[t]},{
begin:/'/,end:/'/,contains:[t]},{begin:/[^\s"'=<>`]+/}]}]}]};return{
name:"HTML, XML",
aliases:["html","xhtml","rss","atom","xjb","xsd","xsl","plist","wsf","svg"],
case_insensitive:!0,contains:[{className:"meta",begin:/<![a-z]/,end:/>/,
relevance:10,contains:[a,o,i,r,{begin:/\[/,end:/\]/,contains:[{className:"meta",
begin:/<![a-z]/,end:/>/,contains:[a,r,o,i]}]}]},e.COMMENT(/<!--/,/-->/,{
relevance:10}),{begin:/<!\[CDATA\[/,end:/\]\]>/,relevance:10},t,{
className:"meta",begin:/<\?xml/,end:/\?>/,relevance:10},{className:"tag",
begin:/<style(?=\s|>)/,end:/>/,keywords:{name:"style"},contains:[c],starts:{
end:/<\/style>/,returnEnd:!0,subLanguage:["css","xml"]}},{className:"tag",
begin:/<script(?=\s|>)/,end:/>/,keywords:{name:"script"},contains:[c],starts:{
end:/<\/script>/,returnEnd:!0,subLanguage:["javascript","handlebars","xml"]}},{
className:"tag",begin:/<>|<\/>/},{className:"tag",
begin:n.concat(/</,n.lookahead(n.concat(s,n.either(/\/>/,/>/,/\s/)))),
end:/\/?>/,contains:[{className:"name",begin:s,relevance:0,starts:c}]},{
className:"tag",begin:n.concat(/<\//,n.lookahead(n.concat(s,/>/))),contains:[{
className:"name",begin:s,relevance:0},{begin:/>/,relevance:0,endsParent:!0}]}]}
},grmr_markdown:e=>{const n={begin:/<\/?[A-Za-z_]/,end:">",subLanguage:"xml",
relevance:0},s={variants:[{begin:/\[.+?\]\[.*?\]/,relevance:0},{
begin:/\[.+?\]\(((data|javascript|mailto):|(?:http|ftp)s?:\/\/).*?\)/,
relevance:2},{
begin:e.regex.concat(/\[.+?\]\(/,/[A-Za-z][A-Za-z0-9+.-]*/,/:\/\/.*?\)/),
relevance:2},{begin:/\[.+?\]\([./?&#].*?\)/,relevance:1},{
begin:/\[.*?\]\(.*?\)/,relevance:0}],returnBegin:!0,contains:[{match:/\[(?=\])/
},{className:"string",relevance:0,begin:"\\[",end:"\\]",excludeBegin:!0,
returnEnd:!0},{className:"link",relevance:0,begin:"\\]\\(",end:"\\)",
excludeBegin:!0,excludeEnd:!0},{className:"symbol",relevance:0,begin:"\\]\\[",
end:"\\]",excludeBegin:!0,excludeEnd:!0}]},t={className:"strong",contains:[],
variants:[{begin:/_{2}/,end:/_{2}/},{begin:/\*{2}/,end:/\*{2}/}]},a={
className:"emphasis",contains:[],variants:[{begin:/\*(?!\*)/,end:/\*/},{
begin:/_(?!_)/,end:/_/,relevance:0}]};t.contains.push(a),a.contains.push(t)
;let r=[n,s]
;return t.contains=t.contains.concat(r),a.contains=a.contains.concat(r),
r=r.concat(t,a),{name:"Markdown",aliases:["md","mkdown","mkd"],contains:[{
className:"section",variants:[{begin:"^#{1,6}",end:"$",contains:r},{
begin:"(?=^.+?\\n[=-]{2,}$)",contains:[{begin:"^[=-]*$"},{begin:"^",end:"\\n",
contains:r}]}]},n,{className:"bullet",begin:"^[ \t]*([*+-]|(\\d+\\.))(?=\\s+)",
end:"\\s+",excludeEnd:!0},t,a,{className:"quote",begin:"^>\\s+",contains:r,
end:"$"},{className:"code",variants:[{begin:"(`{3,})[^`](.|\\n)*?\\1`*[ ]*"},{
begin:"(~{3,})[^~](.|\\n)*?\\1~*[ ]*"},{begin:"```",end:"```+[ ]*$"},{
begin:"~~~",end:"~~~+[ ]*$"},{begin:"`.+?`"},{begin:"(?=^( {4}|\\t))",
contains:[{begin:"^( {4}|\\t)",end:"(\\n)$"}],relevance:0}]},{
begin:"^[-\\*]{3,}",end:"$"},s,{begin:/^\[[^\n]+\]:/,returnBegin:!0,contains:[{
className:"symbol",begin:/\[/,end:/\]/,excludeBegin:!0,excludeEnd:!0},{
className:"link",begin:/:\s*/,end:/$/,excludeBegin:!0}]}]}},grmr_objectivec:e=>{
const n=/[a-zA-Z@][a-zA-Z0-9_]*/,s={$pattern:n,
keyword:["@interface","@class","@protocol","@implementation"]};return{
name:"Objective-C",aliases:["mm","objc","obj-c","obj-c++","objective-c++"],
keywords:{$pattern:n,
keyword:["int","float","while","char","export","sizeof","typedef","const","struct","for","union","unsigned","long","volatile","static","bool","mutable","if","do","return","goto","void","enum","else","break","extern","asm","case","short","default","double","register","explicit","signed","typename","this","switch","continue","wchar_t","inline","readonly","assign","readwrite","self","@synchronized","id","typeof","nonatomic","super","unichar","IBOutlet","IBAction","strong","weak","copy","in","out","inout","bycopy","byref","oneway","__strong","__weak","__block","__autoreleasing","@private","@protected","@public","@try","@property","@end","@throw","@catch","@finally","@autoreleasepool","@synthesize","@dynamic","@selector","@optional","@required","@encode","@package","@import","@defs","@compatibility_alias","__bridge","__bridge_transfer","__bridge_retained","__bridge_retain","__covariant","__contravariant","__kindof","_Nonnull","_Nullable","_Null_unspecified","__FUNCTION__","__PRETTY_FUNCTION__","__attribute__","getter","setter","retain","unsafe_unretained","nonnull","nullable","null_unspecified","null_resettable","class","instancetype","NS_DESIGNATED_INITIALIZER","NS_UNAVAILABLE","NS_REQUIRES_SUPER","NS_RETURNS_INNER_POINTER","NS_INLINE","NS_AVAILABLE","NS_DEPRECATED","NS_ENUM","NS_OPTIONS","NS_SWIFT_UNAVAILABLE","NS_ASSUME_NONNULL_BEGIN","NS_ASSUME_NONNULL_END","NS_REFINED_FOR_SWIFT","NS_SWIFT_NAME","NS_SWIFT_NOTHROW","NS_DURING","NS_HANDLER","NS_ENDHANDLER","NS_VALUERETURN","NS_VOIDRETURN"],
literal:["false","true","FALSE","TRUE","nil","YES","NO","NULL"],
built_in:["BOOL","dispatch_once_t","dispatch_queue_t","dispatch_sync","dispatch_async","dispatch_once"]
},illegal:"</",contains:[{className:"built_in",
begin:"\\b(AV|CA|CF|CG|CI|CL|CM|CN|CT|MK|MP|MTK|MTL|NS|SCN|SK|UI|WK|XC)\\w+"
},e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE,e.C_NUMBER_MODE,e.QUOTE_STRING_MODE,e.APOS_STRING_MODE,{
className:"string",variants:[{begin:'@"',end:'"',illegal:"\\n",
contains:[e.BACKSLASH_ESCAPE]}]},{className:"meta",begin:/#\s*[a-z]+\b/,end:/$/,
keywords:{
keyword:"if else elif endif define undef warning error line pragma ifdef ifndef include"
},contains:[{begin:/\\\n/,relevance:0},e.inherit(e.QUOTE_STRING_MODE,{
className:"string"}),{className:"string",begin:/<.*?>/,end:/$/,illegal:"\\n"
},e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE]},{className:"class",
begin:"("+s.keyword.join("|")+")\\b",end:/(\{|$)/,excludeEnd:!0,keywords:s,
contains:[e.UNDERSCORE_TITLE_MODE]},{begin:"\\."+e.UNDERSCORE_IDENT_RE,
relevance:0}]}},grmr_perl:e=>{const n=e.regex,s=/[dualxmsipngr]{0,12}/,t={
$pattern:/[\w.]+/,
keyword:"abs accept alarm and atan2 bind binmode bless break caller chdir chmod chomp chop chown chr chroot close closedir connect continue cos crypt dbmclose dbmopen defined delete die do dump each else elsif endgrent endhostent endnetent endprotoent endpwent endservent eof eval exec exists exit exp fcntl fileno flock for foreach fork format formline getc getgrent getgrgid getgrnam gethostbyaddr gethostbyname gethostent getlogin getnetbyaddr getnetbyname getnetent getpeername getpgrp getpriority getprotobyname getprotobynumber getprotoent getpwent getpwnam getpwuid getservbyname getservbyport getservent getsockname getsockopt given glob gmtime goto grep gt hex if index int ioctl join keys kill last lc lcfirst length link listen local localtime log lstat lt ma map mkdir msgctl msgget msgrcv msgsnd my ne next no not oct open opendir or ord our pack package pipe pop pos print printf prototype push q|0 qq quotemeta qw qx rand read readdir readline readlink readpipe recv redo ref rename require reset return reverse rewinddir rindex rmdir say scalar seek seekdir select semctl semget semop send setgrent sethostent setnetent setpgrp setpriority setprotoent setpwent setservent setsockopt shift shmctl shmget shmread shmwrite shutdown sin sleep socket socketpair sort splice split sprintf sqrt srand stat state study sub substr symlink syscall sysopen sysread sysseek system syswrite tell telldir tie tied time times tr truncate uc ucfirst umask undef unless unlink unpack unshift untie until use utime values vec wait waitpid wantarray warn when while write x|0 xor y|0"
},a={className:"subst",begin:"[$@]\\{",end:"\\}",keywords:t},r={begin:/->\{/,
end:/\}/},i={variants:[{begin:/\$\d/},{
begin:n.concat(/[$%@](\^\w\b|#\w+(::\w+)*|\{\w+\}|\w+(::\w*)*)/,"(?![A-Za-z])(?![@$%])")
},{begin:/[$%@][^\s\w{]/,relevance:0}]
},o=[e.BACKSLASH_ESCAPE,a,i],c=[/!/,/\//,/\|/,/\?/,/'/,/"/,/#/],l=(e,t,a="\\1")=>{
const r="\\1"===a?a:n.concat(a,t)
;return n.concat(n.concat("(?:",e,")"),t,/(?:\\.|[^\\\/])*?/,r,/(?:\\.|[^\\\/])*?/,a,s)
},d=(e,t,a)=>n.concat(n.concat("(?:",e,")"),t,/(?:\\.|[^\\\/])*?/,a,s),p=[i,e.HASH_COMMENT_MODE,e.COMMENT(/^=\w/,/=cut/,{
endsWithParent:!0}),r,{className:"string",contains:o,variants:[{
begin:"q[qwxr]?\\s*\\(",end:"\\)",relevance:5},{begin:"q[qwxr]?\\s*\\[",
end:"\\]",relevance:5},{begin:"q[qwxr]?\\s*\\{",end:"\\}",relevance:5},{
begin:"q[qwxr]?\\s*\\|",end:"\\|",relevance:5},{begin:"q[qwxr]?\\s*<",end:">",
relevance:5},{begin:"qw\\s+q",end:"q",relevance:5},{begin:"'",end:"'",
contains:[e.BACKSLASH_ESCAPE]},{begin:'"',end:'"'},{begin:"`",end:"`",
contains:[e.BACKSLASH_ESCAPE]},{begin:/\{\w+\}/,relevance:0},{
begin:"-?\\w+\\s*=>",relevance:0}]},{className:"number",
begin:"(\\b0[0-7_]+)|(\\b0x[0-9a-fA-F_]+)|(\\b[1-9][0-9_]*(\\.[0-9_]+)?)|[0_]\\b",
relevance:0},{
begin:"(\\/\\/|"+e.RE_STARTERS_RE+"|\\b(split|return|print|reverse|grep)\\b)\\s*",
keywords:"split return print reverse grep",relevance:0,
contains:[e.HASH_COMMENT_MODE,{className:"regexp",variants:[{
begin:l("s|tr|y",n.either(...c,{capture:!0}))},{begin:l("s|tr|y","\\(","\\)")},{
begin:l("s|tr|y","\\[","\\]")},{begin:l("s|tr|y","\\{","\\}")}],relevance:2},{
className:"regexp",variants:[{begin:/(m|qr)\/\//,relevance:0},{
begin:d("(?:m|qr)?",/\//,/\//)},{begin:d("m|qr",n.either(...c,{capture:!0
}),/\1/)},{begin:d("m|qr",/\(/,/\)/)},{begin:d("m|qr",/\[/,/\]/)},{
begin:d("m|qr",/\{/,/\}/)}]}]},{className:"function",beginKeywords:"sub",
end:"(\\s*\\(.*?\\))?[;{]",excludeEnd:!0,relevance:5,contains:[e.TITLE_MODE]},{
begin:"-\\w\\b",relevance:0},{begin:"^__DATA__$",end:"^__END__$",
subLanguage:"mojolicious",contains:[{begin:"^@@.*",end:"$",className:"comment"}]
}];return a.contains=p,r.contains=p,{name:"Perl",aliases:["pl","pm"],keywords:t,
contains:p}},grmr_php:e=>{
const n=e.regex,s="[a-zA-Z0-9_\x7f-\xff]*(?![A-Za-z0-9])(?![$]))",t=n.concat("([a-zA-Z_\\x7f-\\xff]",s),a=n.concat("([A-Z]",s),r={
scope:"variable",match:"\\$+"+t},i={scope:"subst",variants:[{begin:/\$\w+/},{
begin:/\{\$/,end:/\}/}]},o=e.inherit(e.APOS_STRING_MODE,{illegal:null
}),c="[ \t\n]",l={scope:"string",variants:[e.inherit(e.QUOTE_STRING_MODE,{
illegal:null,contains:e.QUOTE_STRING_MODE.contains.concat(i)
}),o,e.END_SAME_AS_BEGIN({begin:/<<<[ \t]*(\w+)\n/,end:/[ \t]*(\w+)\b/,
contains:e.QUOTE_STRING_MODE.contains.concat(i)})]},d={scope:"number",
variants:[{begin:"\\b0[bB][01]+(?:_[01]+)*\\b"},{
begin:"\\b0[oO][0-7]+(?:_[0-7]+)*\\b"},{
begin:"\\b0[xX][\\da-fA-F]+(?:_[\\da-fA-F]+)*\\b"},{
begin:"(?:\\b\\d+(?:_\\d+)*(\\.(?:\\d+(?:_\\d+)*))?|\\B\\.\\d+)(?:[eE][+-]?\\d+)?"
}],relevance:0
},p=["__CLASS__","__DIR__","__FILE__","__FUNCTION__","__COMPILER_HALT_OFFSET__","__LINE__","__METHOD__","__NAMESPACE__","__TRAIT__","die","echo","exit","include","include_once","print","require","require_once","array","abstract","and","as","binary","bool","boolean","break","callable","case","catch","class","clone","const","continue","declare","default","do","double","else","elseif","empty","enddeclare","endfor","endforeach","endif","endswitch","endwhile","enum","eval","extends","final","finally","float","for","foreach","from","global","goto","if","implements","instanceof","insteadof","int","integer","interface","isset","iterable","list","match|0","mixed","new","never","object","or","private","protected","public","readonly","real","return","string","switch","throw","trait","try","unset","use","var","void","while","xor","yield"],m=["Error|0","AppendIterator","ArgumentCountError","ArithmeticError","ArrayIterator","ArrayObject","AssertionError","BadFunctionCallException","BadMethodCallException","CachingIterator","CallbackFilterIterator","CompileError","Countable","DirectoryIterator","DivisionByZeroError","DomainException","EmptyIterator","ErrorException","Exception","FilesystemIterator","FilterIterator","GlobIterator","InfiniteIterator","InvalidArgumentException","IteratorIterator","LengthException","LimitIterator","LogicException","MultipleIterator","NoRewindIterator","OutOfBoundsException","OutOfRangeException","OuterIterator","OverflowException","ParentIterator","ParseError","RangeException","RecursiveArrayIterator","RecursiveCachingIterator","RecursiveCallbackFilterIterator","RecursiveDirectoryIterator","RecursiveFilterIterator","RecursiveIterator","RecursiveIteratorIterator","RecursiveRegexIterator","RecursiveTreeIterator","RegexIterator","RuntimeException","SeekableIterator","SplDoublyLinkedList","SplFileInfo","SplFileObject","SplFixedArray","SplHeap","SplMaxHeap","SplMinHeap","SplObjectStorage","SplObserver","SplPriorityQueue","SplQueue","SplStack","SplSubject","SplTempFileObject","TypeError","UnderflowException","UnexpectedValueException","UnhandledMatchError","ArrayAccess","BackedEnum","Closure","Fiber","Generator","Iterator","IteratorAggregate","Serializable","Stringable","Throwable","Traversable","UnitEnum","WeakReference","WeakMap","Directory","__PHP_Incomplete_Class","parent","php_user_filter","self","static","stdClass"],u={
keyword:p,literal:(e=>{const n=[];return["false","null","true"].forEach((e=>{
n.push(e),e.toLowerCase()===e?n.push(e.toUpperCase()):n.push(e.toLowerCase())
})),n})(),built_in:m},b=e=>e.map((e=>e.replace(/\|\d+$/,""))),g={variants:[{
match:[/new/,n.concat(c,"+"),n.concat("(?!",b(m).join("\\b|"),"\\b)"),n.concat(/\\?/,t),n.concat(c,"*",/\(/)],
scope:{1:"keyword",4:"title.class"}}]},_={relevance:0,
match:[/\b/,n.concat("(?!fn\\b|function\\b|",b(p).join("\\b|"),"|",b(m).join("\\b|"),"\\b)"),t,n.concat(c,"*"),n.lookahead(/(?=\()/)],
scope:{3:"title.function.invoke"}},v=n.concat(t,"\\b(?!\\()"),f={variants:[{
match:[n.concat(/::/,n.lookahead(/(?!class\b)/)),v],scope:{2:"variable.constant"
}},{match:[/::/,/class/],scope:{2:"variable.language"}},{
match:[a,n.concat("::",n.lookahead(/(?!class\b)/))],scope:{1:"title.class"}},{
match:[a,/::/,/class/],scope:{1:"title.class",3:"variable.language"}}]};return{
case_insensitive:!1,keywords:u,
contains:[e.HASH_COMMENT_MODE,e.COMMENT("//","$"),e.COMMENT("/\\*","\\*/",{
contains:[{scope:"doctag",match:"@[A-Za-z]+"}]}),{match:/__halt_compiler\(\);/,
keywords:"__halt_compiler",starts:{scope:"comment",end:e.MATCH_NOTHING_RE,
contains:[{match:/\?>/,scope:"meta",endsParent:!0}]}},{scope:"meta",variants:[{
begin:/<\?php/,relevance:10},{begin:/<\?[=]?/},{begin:/\?>/}]},{
scope:"variable.language",match:/\$this\b/},r,_,f,{
match:[/const/,/\s/,t,/\s*=/],scope:{1:"keyword",3:"variable.constant"}},g,{
scope:"function",relevance:0,beginKeywords:"fn function",end:/[;{]/,
excludeEnd:!0,illegal:"[$%\\[]",contains:[{beginKeywords:"use"
},e.UNDERSCORE_TITLE_MODE,{begin:"=>",endsParent:!0},{scope:"params",
begin:"\\(",end:"\\)",excludeBegin:!0,excludeEnd:!0,keywords:u,
contains:["self",r,f,e.C_BLOCK_COMMENT_MODE,l,d]}]},{scope:"class",variants:[{
beginKeywords:"enum",illegal:/[($"]/},{beginKeywords:"class interface trait",
illegal:/[:($"]/}],relevance:0,end:/\{/,excludeEnd:!0,contains:[{
beginKeywords:"extends implements"},e.UNDERSCORE_TITLE_MODE]},{
beginKeywords:"namespace",relevance:0,end:";",illegal:/[.']/,
contains:[e.inherit(e.UNDERSCORE_TITLE_MODE,{scope:"title.class"})]},{
beginKeywords:"use",relevance:0,end:";",contains:[{
match:/\b(as|const|function)\b/,scope:"keyword"},e.UNDERSCORE_TITLE_MODE]},l,d]}
},grmr_php_template:e=>({name:"PHP template",subLanguage:"xml",contains:[{
begin:/<\?(php|=)?/,end:/\?>/,subLanguage:"php",contains:[{begin:"/\\*",
end:"\\*/",skip:!0},{begin:'b"',end:'"',skip:!0},{begin:"b'",end:"'",skip:!0
},e.inherit(e.APOS_STRING_MODE,{illegal:null,className:null,contains:null,
skip:!0}),e.inherit(e.QUOTE_STRING_MODE,{illegal:null,className:null,
contains:null,skip:!0})]}]}),grmr_plaintext:e=>({name:"Plain text",
aliases:["text","txt"],disableAutodetect:!0}),grmr_python:e=>{
const n=e.regex,s=/[\p{XID_Start}_]\p{XID_Continue}*/u,t=["and","as","assert","async","await","break","class","continue","def","del","elif","else","except","finally","for","from","global","if","import","in","is","lambda","nonlocal|10","not","or","pass","raise","return","try","while","with","yield"],a={
$pattern:/[A-Za-z]\w+|__\w+__/,keyword:t,
built_in:["__import__","abs","all","any","ascii","bin","bool","breakpoint","bytearray","bytes","callable","chr","classmethod","compile","complex","delattr","dict","dir","divmod","enumerate","eval","exec","filter","float","format","frozenset","getattr","globals","hasattr","hash","help","hex","id","input","int","isinstance","issubclass","iter","len","list","locals","map","max","memoryview","min","next","object","oct","open","ord","pow","print","property","range","repr","reversed","round","set","setattr","slice","sorted","staticmethod","str","sum","super","tuple","type","vars","zip"],
literal:["__debug__","Ellipsis","False","None","NotImplemented","True"],
type:["Any","Callable","Coroutine","Dict","List","Literal","Generic","Optional","Sequence","Set","Tuple","Type","Union"]
},r={className:"meta",begin:/^(>>>|\.\.\.) /},i={className:"subst",begin:/\{/,
end:/\}/,keywords:a,illegal:/#/},o={begin:/\{\{/,relevance:0},c={
className:"string",contains:[e.BACKSLASH_ESCAPE],variants:[{
begin:/([uU]|[bB]|[rR]|[bB][rR]|[rR][bB])?'''/,end:/'''/,
contains:[e.BACKSLASH_ESCAPE,r],relevance:10},{
begin:/([uU]|[bB]|[rR]|[bB][rR]|[rR][bB])?"""/,end:/"""/,
contains:[e.BACKSLASH_ESCAPE,r],relevance:10},{
begin:/([fF][rR]|[rR][fF]|[fF])'''/,end:/'''/,
contains:[e.BACKSLASH_ESCAPE,r,o,i]},{begin:/([fF][rR]|[rR][fF]|[fF])"""/,
end:/"""/,contains:[e.BACKSLASH_ESCAPE,r,o,i]},{begin:/([uU]|[rR])'/,end:/'/,
relevance:10},{begin:/([uU]|[rR])"/,end:/"/,relevance:10},{
begin:/([bB]|[bB][rR]|[rR][bB])'/,end:/'/},{begin:/([bB]|[bB][rR]|[rR][bB])"/,
end:/"/},{begin:/([fF][rR]|[rR][fF]|[fF])'/,end:/'/,
contains:[e.BACKSLASH_ESCAPE,o,i]},{begin:/([fF][rR]|[rR][fF]|[fF])"/,end:/"/,
contains:[e.BACKSLASH_ESCAPE,o,i]},e.APOS_STRING_MODE,e.QUOTE_STRING_MODE]
},l="[0-9](_?[0-9])*",d=`(\\b(${l}))?\\.(${l})|\\b(${l})\\.`,p="\\b|"+t.join("|"),m={
className:"number",relevance:0,variants:[{
begin:`(\\b(${l})|(${d}))[eE][+-]?(${l})[jJ]?(?=${p})`},{begin:`(${d})[jJ]?`},{
begin:`\\b([1-9](_?[0-9])*|0+(_?0)*)[lLjJ]?(?=${p})`},{
begin:`\\b0[bB](_?[01])+[lL]?(?=${p})`},{begin:`\\b0[oO](_?[0-7])+[lL]?(?=${p})`
},{begin:`\\b0[xX](_?[0-9a-fA-F])+[lL]?(?=${p})`},{begin:`\\b(${l})[jJ](?=${p})`
}]},u={className:"comment",begin:n.lookahead(/# type:/),end:/$/,keywords:a,
contains:[{begin:/# type:/},{begin:/#/,end:/\b\B/,endsWithParent:!0}]},b={
className:"params",variants:[{className:"",begin:/\(\s*\)/,skip:!0},{begin:/\(/,
end:/\)/,excludeBegin:!0,excludeEnd:!0,keywords:a,
contains:["self",r,m,c,e.HASH_COMMENT_MODE]}]};return i.contains=[c,m,r],{
name:"Python",aliases:["py","gyp","ipython"],unicodeRegex:!0,keywords:a,
illegal:/(<\/|->|\?)|=>/,contains:[r,m,{begin:/\bself\b/},{beginKeywords:"if",
relevance:0},c,u,e.HASH_COMMENT_MODE,{match:[/\bdef/,/\s+/,s],scope:{
1:"keyword",3:"title.function"},contains:[b]},{variants:[{
match:[/\bclass/,/\s+/,s,/\s*/,/\(\s*/,s,/\s*\)/]},{match:[/\bclass/,/\s+/,s]}],
scope:{1:"keyword",3:"title.class",6:"title.class.inherited"}},{
className:"meta",begin:/^[\t ]*@/,end:/(?=#)|$/,contains:[m,b,c]}]}},
grmr_python_repl:e=>({aliases:["pycon"],contains:[{className:"meta",starts:{
end:/ |$/,starts:{end:"$",subLanguage:"python"}},variants:[{
begin:/^>>>(?=[ ]|$)/},{begin:/^\.\.\.(?=[ ]|$)/}]}]}),grmr_r:e=>{
const n=e.regex,s=/(?:(?:[a-zA-Z]|\.[._a-zA-Z])[._a-zA-Z0-9]*)|\.(?!\d)/,t=n.either(/0[xX][0-9a-fA-F]+\.[0-9a-fA-F]*[pP][+-]?\d+i?/,/0[xX][0-9a-fA-F]+(?:[pP][+-]?\d+)?[Li]?/,/(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][+-]?\d+)?[Li]?/),a=/[=!<>:]=|\|\||&&|:::?|<-|<<-|->>|->|\|>|[-+*\/?!$&|:<=>@^~]|\*\*/,r=n.either(/[()]/,/[{}]/,/\[\[/,/[[\]]/,/\\/,/,/)
;return{name:"R",keywords:{$pattern:s,
keyword:"function if in break next repeat else for while",
literal:"NULL NA TRUE FALSE Inf NaN NA_integer_|10 NA_real_|10 NA_character_|10 NA_complex_|10",
built_in:"LETTERS letters month.abb month.name pi T F abs acos acosh all any anyNA Arg as.call as.character as.complex as.double as.environment as.integer as.logical as.null.default as.numeric as.raw asin asinh atan atanh attr attributes baseenv browser c call ceiling class Conj cos cosh cospi cummax cummin cumprod cumsum digamma dim dimnames emptyenv exp expression floor forceAndCall gamma gc.time globalenv Im interactive invisible is.array is.atomic is.call is.character is.complex is.double is.environment is.expression is.finite is.function is.infinite is.integer is.language is.list is.logical is.matrix is.na is.name is.nan is.null is.numeric is.object is.pairlist is.raw is.recursive is.single is.symbol lazyLoadDBfetch length lgamma list log max min missing Mod names nargs nzchar oldClass on.exit pos.to.env proc.time prod quote range Re rep retracemem return round seq_along seq_len seq.int sign signif sin sinh sinpi sqrt standardGeneric substitute sum switch tan tanh tanpi tracemem trigamma trunc unclass untracemem UseMethod xtfrm"
},contains:[e.COMMENT(/#'/,/$/,{contains:[{scope:"doctag",match:/@examples/,
starts:{end:n.lookahead(n.either(/\n^#'\s*(?=@[a-zA-Z]+)/,/\n^(?!#')/)),
endsParent:!0}},{scope:"doctag",begin:"@param",end:/$/,contains:[{
scope:"variable",variants:[{match:s},{match:/`(?:\\.|[^`\\])+`/}],endsParent:!0
}]},{scope:"doctag",match:/@[a-zA-Z]+/},{scope:"keyword",match:/\\[a-zA-Z]+/}]
}),e.HASH_COMMENT_MODE,{scope:"string",contains:[e.BACKSLASH_ESCAPE],
variants:[e.END_SAME_AS_BEGIN({begin:/[rR]"(-*)\(/,end:/\)(-*)"/
}),e.END_SAME_AS_BEGIN({begin:/[rR]"(-*)\{/,end:/\}(-*)"/
}),e.END_SAME_AS_BEGIN({begin:/[rR]"(-*)\[/,end:/\](-*)"/
}),e.END_SAME_AS_BEGIN({begin:/[rR]'(-*)\(/,end:/\)(-*)'/
}),e.END_SAME_AS_BEGIN({begin:/[rR]'(-*)\{/,end:/\}(-*)'/
}),e.END_SAME_AS_BEGIN({begin:/[rR]'(-*)\[/,end:/\](-*)'/}),{begin:'"',end:'"',
relevance:0},{begin:"'",end:"'",relevance:0}]},{relevance:0,variants:[{scope:{
1:"operator",2:"number"},match:[a,t]},{scope:{1:"operator",2:"number"},
match:[/%[^%]*%/,t]},{scope:{1:"punctuation",2:"number"},match:[r,t]},{scope:{
2:"number"},match:[/[^a-zA-Z0-9._]|^/,t]}]},{scope:{3:"operator"},
match:[s,/\s+/,/<-/,/\s+/]},{scope:"operator",relevance:0,variants:[{match:a},{
match:/%[^%]*%/}]},{scope:"punctuation",relevance:0,match:r},{begin:"`",end:"`",
contains:[{begin:/\\./}]}]}},grmr_ruby:e=>{
const n=e.regex,s="([a-zA-Z_]\\w*[!?=]?|[-+~]@|<<|>>|=~|===?|<=>|[<>]=?|\\*\\*|[-/+%^&*~`|]|\\[\\]=?)",t={
keyword:"and then defined module in return redo if BEGIN retry end for self when next until do begin unless END rescue else break undef not super class case require yield alias while ensure elsif or include attr_reader attr_writer attr_accessor __FILE__",
built_in:"proc lambda",literal:"true false nil"},a={className:"doctag",
begin:"@[A-Za-z]+"},r={begin:"#<",end:">"},i=[e.COMMENT("#","$",{contains:[a]
}),e.COMMENT("^=begin","^=end",{contains:[a],relevance:10
}),e.COMMENT("^__END__","\\n$")],o={className:"subst",begin:/#\{/,end:/\}/,
keywords:t},c={className:"string",contains:[e.BACKSLASH_ESCAPE,o],variants:[{
begin:/'/,end:/'/},{begin:/"/,end:/"/},{begin:/`/,end:/`/},{begin:/%[qQwWx]?\(/,
end:/\)/},{begin:/%[qQwWx]?\[/,end:/\]/},{begin:/%[qQwWx]?\{/,end:/\}/},{
begin:/%[qQwWx]?</,end:/>/},{begin:/%[qQwWx]?\//,end:/\//},{begin:/%[qQwWx]?%/,
end:/%/},{begin:/%[qQwWx]?-/,end:/-/},{begin:/%[qQwWx]?\|/,end:/\|/},{
begin:/\B\?(\\\d{1,3})/},{begin:/\B\?(\\x[A-Fa-f0-9]{1,2})/},{
begin:/\B\?(\\u\{?[A-Fa-f0-9]{1,6}\}?)/},{
begin:/\B\?(\\M-\\C-|\\M-\\c|\\c\\M-|\\M-|\\C-\\M-)[\x20-\x7e]/},{
begin:/\B\?\\(c|C-)[\x20-\x7e]/},{begin:/\B\?\\?\S/},{
begin:n.concat(/<<[-~]?'?/,n.lookahead(/(\w+)(?=\W)[^\n]*\n(?:[^\n]*\n)*?\s*\1\b/)),
contains:[e.END_SAME_AS_BEGIN({begin:/(\w+)/,end:/(\w+)/,
contains:[e.BACKSLASH_ESCAPE,o]})]}]},l="[0-9](_?[0-9])*",d={className:"number",
relevance:0,variants:[{
begin:`\\b([1-9](_?[0-9])*|0)(\\.(${l}))?([eE][+-]?(${l})|r)?i?\\b`},{
begin:"\\b0[dD][0-9](_?[0-9])*r?i?\\b"},{begin:"\\b0[bB][0-1](_?[0-1])*r?i?\\b"
},{begin:"\\b0[oO][0-7](_?[0-7])*r?i?\\b"},{
begin:"\\b0[xX][0-9a-fA-F](_?[0-9a-fA-F])*r?i?\\b"},{
begin:"\\b0(_?[0-7])+r?i?\\b"}]},p={className:"params",begin:"\\(",end:"\\)",
endsParent:!0,keywords:t},m=[c,{className:"class",beginKeywords:"class module",
end:"$|;",illegal:/=/,contains:[e.inherit(e.TITLE_MODE,{
begin:"[A-Za-z_]\\w*(::\\w+)*(\\?|!)?"}),{begin:"<\\s*",contains:[{
begin:"("+e.IDENT_RE+"::)?"+e.IDENT_RE,relevance:0}]}].concat(i)},{
className:"function",begin:n.concat(/def\s+/,n.lookahead(s+"\\s*(\\(|;|$)")),
relevance:0,keywords:"def",end:"$|;",contains:[e.inherit(e.TITLE_MODE,{begin:s
}),p].concat(i)},{begin:e.IDENT_RE+"::"},{className:"symbol",
begin:e.UNDERSCORE_IDENT_RE+"(!|\\?)?:",relevance:0},{className:"symbol",
begin:":(?!\\s)",contains:[c,{begin:s}],relevance:0},d,{className:"variable",
begin:"(\\$\\W)|((\\$|@@?)(\\w+))(?=[^@$?])(?![A-Za-z])(?![@$?'])"},{
className:"params",begin:/\|/,end:/\|/,relevance:0,keywords:t},{
begin:"("+e.RE_STARTERS_RE+"|unless)\\s*",keywords:"unless",contains:[{
className:"regexp",contains:[e.BACKSLASH_ESCAPE,o],illegal:/\n/,variants:[{
begin:"/",end:"/[a-z]*"},{begin:/%r\{/,end:/\}[a-z]*/},{begin:"%r\\(",
end:"\\)[a-z]*"},{begin:"%r!",end:"![a-z]*"},{begin:"%r\\[",end:"\\][a-z]*"}]
}].concat(r,i),relevance:0}].concat(r,i);o.contains=m,p.contains=m;const u=[{
begin:/^\s*=>/,starts:{end:"$",contains:m}},{className:"meta",
begin:"^([>?]>|[\\w#]+\\(\\w+\\):\\d+:\\d+>|(\\w+-)?\\d+\\.\\d+\\.\\d+(p\\d+)?[^\\d][^>]+>)(?=[ ])",
starts:{end:"$",contains:m}}];return i.unshift(r),{name:"Ruby",
aliases:["rb","gemspec","podspec","thor","irb"],keywords:t,illegal:/\/\*/,
contains:[e.SHEBANG({binary:"ruby"})].concat(u).concat(i).concat(m)}},
grmr_rust:e=>{const n=e.regex,s={className:"title.function.invoke",relevance:0,
begin:n.concat(/\b/,/(?!let\b)/,e.IDENT_RE,n.lookahead(/\s*\(/))
},t="([ui](8|16|32|64|128|size)|f(32|64))?",a=["drop ","Copy","Send","Sized","Sync","Drop","Fn","FnMut","FnOnce","ToOwned","Clone","Debug","PartialEq","PartialOrd","Eq","Ord","AsRef","AsMut","Into","From","Default","Iterator","Extend","IntoIterator","DoubleEndedIterator","ExactSizeIterator","SliceConcatExt","ToString","assert!","assert_eq!","bitflags!","bytes!","cfg!","col!","concat!","concat_idents!","debug_assert!","debug_assert_eq!","env!","panic!","file!","format!","format_args!","include_bin!","include_str!","line!","local_data_key!","module_path!","option_env!","print!","println!","select!","stringify!","try!","unimplemented!","unreachable!","vec!","write!","writeln!","macro_rules!","assert_ne!","debug_assert_ne!"]
;return{name:"Rust",aliases:["rs"],keywords:{$pattern:e.IDENT_RE+"!?",
type:["i8","i16","i32","i64","i128","isize","u8","u16","u32","u64","u128","usize","f32","f64","str","char","bool","Box","Option","Result","String","Vec"],
keyword:["abstract","as","async","await","become","box","break","const","continue","crate","do","dyn","else","enum","extern","false","final","fn","for","if","impl","in","let","loop","macro","match","mod","move","mut","override","priv","pub","ref","return","self","Self","static","struct","super","trait","true","try","type","typeof","unsafe","unsized","use","virtual","where","while","yield"],
literal:["true","false","Some","None","Ok","Err"],built_in:a},illegal:"</",
contains:[e.C_LINE_COMMENT_MODE,e.COMMENT("/\\*","\\*/",{contains:["self"]
}),e.inherit(e.QUOTE_STRING_MODE,{begin:/b?"/,illegal:null}),{
className:"string",variants:[{begin:/b?r(#*)"(.|\n)*?"\1(?!#)/},{
begin:/b?'\\?(x\w{2}|u\w{4}|U\w{8}|.)'/}]},{className:"symbol",
begin:/'[a-zA-Z_][a-zA-Z0-9_]*/},{className:"number",variants:[{
begin:"\\b0b([01_]+)"+t},{begin:"\\b0o([0-7_]+)"+t},{
begin:"\\b0x([A-Fa-f0-9_]+)"+t},{
begin:"\\b(\\d[\\d_]*(\\.[0-9_]+)?([eE][+-]?[0-9_]+)?)"+t}],relevance:0},{
begin:[/fn/,/\s+/,e.UNDERSCORE_IDENT_RE],className:{1:"keyword",
3:"title.function"}},{className:"meta",begin:"#!?\\[",end:"\\]",contains:[{
className:"string",begin:/"/,end:/"/}]},{
begin:[/let/,/\s+/,/(?:mut\s+)?/,e.UNDERSCORE_IDENT_RE],className:{1:"keyword",
3:"keyword",4:"variable"}},{
begin:[/for/,/\s+/,e.UNDERSCORE_IDENT_RE,/\s+/,/in/],className:{1:"keyword",
3:"variable",5:"keyword"}},{begin:[/type/,/\s+/,e.UNDERSCORE_IDENT_RE],
className:{1:"keyword",3:"title.class"}},{
begin:[/(?:trait|enum|struct|union|impl|for)/,/\s+/,e.UNDERSCORE_IDENT_RE],
className:{1:"keyword",3:"title.class"}},{begin:e.IDENT_RE+"::",keywords:{
keyword:"Self",built_in:a}},{className:"punctuation",begin:"->"},s]}},
grmr_scss:e=>{const n=te(e),s=oe,t=ie,a="@[a-z-]+",r={className:"variable",
begin:"(\\$[a-zA-Z-][a-zA-Z0-9_-]*)\\b"};return{name:"SCSS",case_insensitive:!0,
illegal:"[=/|']",
contains:[e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE,n.CSS_NUMBER_MODE,{
className:"selector-id",begin:"#[A-Za-z0-9_-]+",relevance:0},{
className:"selector-class",begin:"\\.[A-Za-z0-9_-]+",relevance:0
},n.ATTRIBUTE_SELECTOR_MODE,{className:"selector-tag",
begin:"\\b("+ae.join("|")+")\\b",relevance:0},{className:"selector-pseudo",
begin:":("+t.join("|")+")"},{className:"selector-pseudo",
begin:":(:)?("+s.join("|")+")"},r,{begin:/\(/,end:/\)/,
contains:[n.CSS_NUMBER_MODE]},n.CSS_VARIABLE,{className:"attribute",
begin:"\\b("+ce.join("|")+")\\b"},{
begin:"\\b(whitespace|wait|w-resize|visible|vertical-text|vertical-ideographic|uppercase|upper-roman|upper-alpha|underline|transparent|top|thin|thick|text|text-top|text-bottom|tb-rl|table-header-group|table-footer-group|sw-resize|super|strict|static|square|solid|small-caps|separate|se-resize|scroll|s-resize|rtl|row-resize|ridge|right|repeat|repeat-y|repeat-x|relative|progress|pointer|overline|outside|outset|oblique|nowrap|not-allowed|normal|none|nw-resize|no-repeat|no-drop|newspaper|ne-resize|n-resize|move|middle|medium|ltr|lr-tb|lowercase|lower-roman|lower-alpha|loose|list-item|line|line-through|line-edge|lighter|left|keep-all|justify|italic|inter-word|inter-ideograph|inside|inset|inline|inline-block|inherit|inactive|ideograph-space|ideograph-parenthesis|ideograph-numeric|ideograph-alpha|horizontal|hidden|help|hand|groove|fixed|ellipsis|e-resize|double|dotted|distribute|distribute-space|distribute-letter|distribute-all-lines|disc|disabled|default|decimal|dashed|crosshair|collapse|col-resize|circle|char|center|capitalize|break-word|break-all|bottom|both|bolder|bold|block|bidi-override|below|baseline|auto|always|all-scroll|absolute|table|table-cell)\\b"
},{begin:/:/,end:/[;}{]/,
contains:[n.BLOCK_COMMENT,r,n.HEXCOLOR,n.CSS_NUMBER_MODE,e.QUOTE_STRING_MODE,e.APOS_STRING_MODE,n.IMPORTANT]
},{begin:"@(page|font-face)",keywords:{$pattern:a,keyword:"@page @font-face"}},{
begin:"@",end:"[{;]",returnBegin:!0,keywords:{$pattern:/[a-z-]+/,
keyword:"and or not only",attribute:re.join(" ")},contains:[{begin:a,
className:"keyword"},{begin:/[a-z-]+(?=:)/,className:"attribute"
},r,e.QUOTE_STRING_MODE,e.APOS_STRING_MODE,n.HEXCOLOR,n.CSS_NUMBER_MODE]
},n.FUNCTION_DISPATCH]}},grmr_shell:e=>({name:"Shell Session",
aliases:["console","shellsession"],contains:[{className:"meta",
begin:/^\s{0,3}[/~\w\d[\]()@-]*[>%$#][ ]?/,starts:{end:/[^\\](?=\s*$)/,
subLanguage:"bash"}}]}),grmr_sql:e=>{
const n=e.regex,s=e.COMMENT("--","$"),t=["true","false","unknown"],a=["bigint","binary","blob","boolean","char","character","clob","date","dec","decfloat","decimal","float","int","integer","interval","nchar","nclob","national","numeric","real","row","smallint","time","timestamp","varchar","varying","varbinary"],r=["abs","acos","array_agg","asin","atan","avg","cast","ceil","ceiling","coalesce","corr","cos","cosh","count","covar_pop","covar_samp","cume_dist","dense_rank","deref","element","exp","extract","first_value","floor","json_array","json_arrayagg","json_exists","json_object","json_objectagg","json_query","json_table","json_table_primitive","json_value","lag","last_value","lead","listagg","ln","log","log10","lower","max","min","mod","nth_value","ntile","nullif","percent_rank","percentile_cont","percentile_disc","position","position_regex","power","rank","regr_avgx","regr_avgy","regr_count","regr_intercept","regr_r2","regr_slope","regr_sxx","regr_sxy","regr_syy","row_number","sin","sinh","sqrt","stddev_pop","stddev_samp","substring","substring_regex","sum","tan","tanh","translate","translate_regex","treat","trim","trim_array","unnest","upper","value_of","var_pop","var_samp","width_bucket"],i=["create table","insert into","primary key","foreign key","not null","alter table","add constraint","grouping sets","on overflow","character set","respect nulls","ignore nulls","nulls first","nulls last","depth first","breadth first"],o=r,c=["abs","acos","all","allocate","alter","and","any","are","array","array_agg","array_max_cardinality","as","asensitive","asin","asymmetric","at","atan","atomic","authorization","avg","begin","begin_frame","begin_partition","between","bigint","binary","blob","boolean","both","by","call","called","cardinality","cascaded","case","cast","ceil","ceiling","char","char_length","character","character_length","check","classifier","clob","close","coalesce","collate","collect","column","commit","condition","connect","constraint","contains","convert","copy","corr","corresponding","cos","cosh","count","covar_pop","covar_samp","create","cross","cube","cume_dist","current","current_catalog","current_date","current_default_transform_group","current_path","current_role","current_row","current_schema","current_time","current_timestamp","current_path","current_role","current_transform_group_for_type","current_user","cursor","cycle","date","day","deallocate","dec","decimal","decfloat","declare","default","define","delete","dense_rank","deref","describe","deterministic","disconnect","distinct","double","drop","dynamic","each","element","else","empty","end","end_frame","end_partition","end-exec","equals","escape","every","except","exec","execute","exists","exp","external","extract","false","fetch","filter","first_value","float","floor","for","foreign","frame_row","free","from","full","function","fusion","get","global","grant","group","grouping","groups","having","hold","hour","identity","in","indicator","initial","inner","inout","insensitive","insert","int","integer","intersect","intersection","interval","into","is","join","json_array","json_arrayagg","json_exists","json_object","json_objectagg","json_query","json_table","json_table_primitive","json_value","lag","language","large","last_value","lateral","lead","leading","left","like","like_regex","listagg","ln","local","localtime","localtimestamp","log","log10","lower","match","match_number","match_recognize","matches","max","member","merge","method","min","minute","mod","modifies","module","month","multiset","national","natural","nchar","nclob","new","no","none","normalize","not","nth_value","ntile","null","nullif","numeric","octet_length","occurrences_regex","of","offset","old","omit","on","one","only","open","or","order","out","outer","over","overlaps","overlay","parameter","partition","pattern","per","percent","percent_rank","percentile_cont","percentile_disc","period","portion","position","position_regex","power","precedes","precision","prepare","primary","procedure","ptf","range","rank","reads","real","recursive","ref","references","referencing","regr_avgx","regr_avgy","regr_count","regr_intercept","regr_r2","regr_slope","regr_sxx","regr_sxy","regr_syy","release","result","return","returns","revoke","right","rollback","rollup","row","row_number","rows","running","savepoint","scope","scroll","search","second","seek","select","sensitive","session_user","set","show","similar","sin","sinh","skip","smallint","some","specific","specifictype","sql","sqlexception","sqlstate","sqlwarning","sqrt","start","static","stddev_pop","stddev_samp","submultiset","subset","substring","substring_regex","succeeds","sum","symmetric","system","system_time","system_user","table","tablesample","tan","tanh","then","time","timestamp","timezone_hour","timezone_minute","to","trailing","translate","translate_regex","translation","treat","trigger","trim","trim_array","true","truncate","uescape","union","unique","unknown","unnest","update","upper","user","using","value","values","value_of","var_pop","var_samp","varbinary","varchar","varying","versioning","when","whenever","where","width_bucket","window","with","within","without","year","add","asc","collation","desc","final","first","last","view"].filter((e=>!r.includes(e))),l={
begin:n.concat(/\b/,n.either(...o),/\s*\(/),relevance:0,keywords:{built_in:o}}
;return{name:"SQL",case_insensitive:!0,illegal:/[{}]|<\//,keywords:{
$pattern:/\b[\w\.]+/,keyword:((e,{exceptions:n,when:s}={})=>{const t=s
;return n=n||[],e.map((e=>e.match(/\|\d+$/)||n.includes(e)?e:t(e)?e+"|0":e))
})(c,{when:e=>e.length<3}),literal:t,type:a,
built_in:["current_catalog","current_date","current_default_transform_group","current_path","current_role","current_schema","current_transform_group_for_type","current_user","session_user","system_time","system_user","current_time","localtime","current_timestamp","localtimestamp"]
},contains:[{begin:n.either(...i),relevance:0,keywords:{$pattern:/[\w\.]+/,
keyword:c.concat(i),literal:t,type:a}},{className:"type",
begin:n.either("double precision","large object","with timezone","without timezone")
},l,{className:"variable",begin:/@[a-z0-9]+/},{className:"string",variants:[{
begin:/'/,end:/'/,contains:[{begin:/''/}]}]},{begin:/"/,end:/"/,contains:[{
begin:/""/}]},e.C_NUMBER_MODE,e.C_BLOCK_COMMENT_MODE,s,{className:"operator",
begin:/[-+*/=%^~]|&&?|\|\|?|!=?|<(?:=>?|<|>)?|>[>=]?/,relevance:0}]}},
grmr_swift:e=>{const n={match:/\s+/,relevance:0},s=e.COMMENT("/\\*","\\*/",{
contains:["self"]}),t=[e.C_LINE_COMMENT_MODE,s],a={match:[/\./,_(...xe,...ke)],
className:{2:"keyword"}},r={match:g(/\./,_(...Me)),relevance:0
},i=Me.filter((e=>"string"==typeof e)).concat(["_|0"]),o={variants:[{
className:"keyword",
match:_(...Me.filter((e=>"string"!=typeof e)).concat(Oe).map(Ne),...ke)}]},c={
$pattern:_(/\b\w+/,/#\w+/),keyword:i.concat(Ae),literal:Se},l=[a,r,o],d=[{
match:g(/\./,_(...Te)),relevance:0},{className:"built_in",
match:g(/\b/,_(...Te),/(?=\()/)}],p={match:/->/,relevance:0},u=[p,{
className:"operator",relevance:0,variants:[{match:Re},{match:`\\.(\\.|${qe})+`}]
}],b="([0-9a-fA-F]_*)+",v={className:"number",relevance:0,variants:[{
match:"\\b(([0-9]_*)+)(\\.(([0-9]_*)+))?([eE][+-]?(([0-9]_*)+))?\\b"},{
match:`\\b0x(${b})(\\.(${b}))?([pP][+-]?(([0-9]_*)+))?\\b`},{
match:/\b0o([0-7]_*)+\b/},{match:/\b0b([01]_*)+\b/}]},f=(e="")=>({
className:"subst",variants:[{match:g(/\\/,e,/[0\\tnr"']/)},{
match:g(/\\/,e,/u\{[0-9a-fA-F]{1,8}\}/)}]}),h=(e="")=>({className:"subst",
match:g(/\\/,e,/[\t ]*(?:[\r\n]|\r\n)/)}),E=(e="")=>({className:"subst",
label:"interpol",begin:g(/\\/,e,/\(/),end:/\)/}),w=(e="")=>({begin:g(e,/"""/),
end:g(/"""/,e),contains:[f(e),h(e),E(e)]}),y=(e="")=>({begin:g(e,/"/),
end:g(/"/,e),contains:[f(e),E(e)]}),N={className:"string",
variants:[w(),w("#"),w("##"),w("###"),y(),y("#"),y("##"),y("###")]},x={
match:g(/`/,Le,/`/)},k=[x,{className:"variable",match:/\$\d+/},{
className:"variable",match:`\\$${Ie}+`}],O=[{match:/(@|#(un)?)available/,
className:"keyword",starts:{contains:[{begin:/\(/,end:/\)/,keywords:Ue,
contains:[...u,v,N]}]}},{className:"keyword",match:g(/@/,_(...ze))},{
className:"meta",match:g(/@/,Le)}],M={match:m(/\b[A-Z]/),relevance:0,contains:[{
className:"type",
match:g(/(AV|CA|CF|CG|CI|CL|CM|CN|CT|MK|MP|MTK|MTL|NS|SCN|SK|UI|WK|XC)/,Ie,"+")
},{className:"type",match:Be,relevance:0},{match:/[?!]+/,relevance:0},{
match:/\.\.\./,relevance:0},{match:g(/\s+&\s+/,m(Be)),relevance:0}]},S={
begin:/</,end:/>/,keywords:c,contains:[...t,...l,...O,p,M]};M.contains.push(S)
;const C={begin:/\(/,end:/\)/,relevance:0,keywords:c,contains:["self",{
match:g(Le,/\s*:/),keywords:"_|0",relevance:0
},...t,...l,...d,...u,v,N,...k,...O,M]},A={begin:/</,end:/>/,contains:[...t,M]
},T={begin:/\(/,end:/\)/,keywords:c,contains:[{
begin:_(m(g(Le,/\s*:/)),m(g(Le,/\s+/,Le,/\s*:/))),end:/:/,relevance:0,
contains:[{className:"keyword",match:/\b_\b/},{className:"params",match:Le}]
},...t,...l,...u,v,N,...O,M,C],endsParent:!0,illegal:/["']/},$={
match:[/func/,/\s+/,_(x.match,Le,Re)],className:{1:"keyword",3:"title.function"
},contains:[A,T,n],illegal:[/\[/,/%/]},q={
match:[/\b(?:subscript|init[?!]?)/,/\s*(?=[<(])/],className:{1:"keyword"},
contains:[A,T,n],illegal:/\[|%/},R={match:[/operator/,/\s+/,Re],className:{
1:"keyword",3:"title"}},D={begin:[/precedencegroup/,/\s+/,Be],className:{
1:"keyword",3:"title"},contains:[M],keywords:[...Ce,...Se],end:/}/}
;for(const e of N.variants){const n=e.contains.find((e=>"interpol"===e.label))
;n.keywords=c;const s=[...l,...d,...u,v,N,...k];n.contains=[...s,{begin:/\(/,
end:/\)/,contains:["self",...s]}]}return{name:"Swift",keywords:c,
contains:[...t,$,q,{beginKeywords:"struct protocol class extension enum actor",
end:"\\{",excludeEnd:!0,keywords:c,contains:[e.inherit(e.TITLE_MODE,{
className:"title.class",begin:/[A-Za-z$_][\u00C0-\u02B80-9A-Za-z$_]*/}),...l]
},R,D,{beginKeywords:"import",end:/$/,contains:[...t],relevance:0
},...l,...d,...u,v,N,...k,...O,M,C]}},grmr_typescript:e=>{
const n=ye(e),s=["any","void","number","boolean","string","object","never","enum"],t={
beginKeywords:"namespace",end:/\{/,excludeEnd:!0,
contains:[n.exports.CLASS_REFERENCE]},a={beginKeywords:"interface",end:/\{/,
excludeEnd:!0,keywords:{keyword:"interface extends",built_in:s},
contains:[n.exports.CLASS_REFERENCE]},r={$pattern:be,
keyword:ge.concat(["type","namespace","typedef","interface","public","private","protected","implements","declare","abstract","readonly"]),
literal:_e,built_in:we.concat(s),"variable.language":Ee},i={className:"meta",
begin:"@[A-Za-z$_][0-9A-Za-z$_]*"},o=(e,n,s)=>{
const t=e.contains.findIndex((e=>e.label===n))
;if(-1===t)throw Error("can not find mode to replace");e.contains.splice(t,1,s)}
;return Object.assign(n.keywords,r),
n.exports.PARAMS_CONTAINS.push(i),n.contains=n.contains.concat([i,t,a]),
o(n,"shebang",e.SHEBANG()),o(n,"use_strict",{className:"meta",relevance:10,
begin:/^\s*['"]use strict['"]/
}),n.contains.find((e=>"func.def"===e.label)).relevance=0,Object.assign(n,{
name:"TypeScript",aliases:["ts","tsx"]}),n},grmr_vbnet:e=>{
const n=e.regex,s=/\d{1,2}\/\d{1,2}\/\d{4}/,t=/\d{4}-\d{1,2}-\d{1,2}/,a=/(\d|1[012])(:\d+){0,2} *(AM|PM)/,r=/\d{1,2}(:\d{1,2}){1,2}/,i={
className:"literal",variants:[{begin:n.concat(/# */,n.either(t,s),/ *#/)},{
begin:n.concat(/# */,r,/ *#/)},{begin:n.concat(/# */,a,/ *#/)},{
begin:n.concat(/# */,n.either(t,s),/ +/,n.either(a,r),/ *#/)}]
},o=e.COMMENT(/'''/,/$/,{contains:[{className:"doctag",begin:/<\/?/,end:/>/}]
}),c=e.COMMENT(null,/$/,{variants:[{begin:/'/},{begin:/([\t ]|^)REM(?=\s)/}]})
;return{name:"Visual Basic .NET",aliases:["vb"],case_insensitive:!0,
classNameAliases:{label:"symbol"},keywords:{
keyword:"addhandler alias aggregate ansi as async assembly auto binary by byref byval call case catch class compare const continue custom declare default delegate dim distinct do each equals else elseif end enum erase error event exit explicit finally for friend from function get global goto group handles if implements imports in inherits interface into iterator join key let lib loop me mid module mustinherit mustoverride mybase myclass namespace narrowing new next notinheritable notoverridable of off on operator option optional order overloads overridable overrides paramarray partial preserve private property protected public raiseevent readonly redim removehandler resume return select set shadows shared skip static step stop structure strict sub synclock take text then throw to try unicode until using when where while widening with withevents writeonly yield",
built_in:"addressof and andalso await directcast gettype getxmlnamespace is isfalse isnot istrue like mod nameof new not or orelse trycast typeof xor cbool cbyte cchar cdate cdbl cdec cint clng cobj csbyte cshort csng cstr cuint culng cushort",
type:"boolean byte char date decimal double integer long object sbyte short single string uinteger ulong ushort",
literal:"true false nothing"},
illegal:"//|\\{|\\}|endif|gosub|variant|wend|^\\$ ",contains:[{
className:"string",begin:/"(""|[^/n])"C\b/},{className:"string",begin:/"/,
end:/"/,illegal:/\n/,contains:[{begin:/""/}]},i,{className:"number",relevance:0,
variants:[{begin:/\b\d[\d_]*((\.[\d_]+(E[+-]?[\d_]+)?)|(E[+-]?[\d_]+))[RFD@!#]?/
},{begin:/\b\d[\d_]*((U?[SIL])|[%&])?/},{begin:/&H[\dA-F_]+((U?[SIL])|[%&])?/},{
begin:/&O[0-7_]+((U?[SIL])|[%&])?/},{begin:/&B[01_]+((U?[SIL])|[%&])?/}]},{
className:"label",begin:/^\w+:/},o,c,{className:"meta",
begin:/[\t ]*#(const|disable|else|elseif|enable|end|externalsource|if|region)\b/,
end:/$/,keywords:{
keyword:"const disable else elseif enable end externalsource if region then"},
contains:[c]}]}},grmr_yaml:e=>{
const n="true false yes no null",s="[\\w#;/?:@&=+$,.~*'()[\\]]+",t={
className:"string",relevance:0,variants:[{begin:/'/,end:/'/},{begin:/"/,end:/"/
},{begin:/\S+/}],contains:[e.BACKSLASH_ESCAPE,{className:"template-variable",
variants:[{begin:/\{\{/,end:/\}\}/},{begin:/%\{/,end:/\}/}]}]},a=e.inherit(t,{
variants:[{begin:/'/,end:/'/},{begin:/"/,end:/"/},{begin:/[^\s,{}[\]]+/}]}),r={
end:",",endsWithParent:!0,excludeEnd:!0,keywords:n,relevance:0},i={begin:/\{/,
end:/\}/,contains:[r],illegal:"\\n",relevance:0},o={begin:"\\[",end:"\\]",
contains:[r],illegal:"\\n",relevance:0},c=[{className:"attr",variants:[{
begin:"\\w[\\w :\\/.-]*:(?=[ \t]|$)"},{begin:'"\\w[\\w :\\/.-]*":(?=[ \t]|$)'},{
begin:"'\\w[\\w :\\/.-]*':(?=[ \t]|$)"}]},{className:"meta",begin:"^---\\s*$",
relevance:10},{className:"string",
begin:"[\\|>]([1-9]?[+-])?[ ]*\\n( +)[^ ][^\\n]*\\n(\\2[^\\n]+\\n?)*"},{
begin:"<%[%=-]?",end:"[%-]?%>",subLanguage:"ruby",excludeBegin:!0,excludeEnd:!0,
relevance:0},{className:"type",begin:"!\\w+!"+s},{className:"type",
begin:"!<"+s+">"},{className:"type",begin:"!"+s},{className:"type",begin:"!!"+s
},{className:"meta",begin:"&"+e.UNDERSCORE_IDENT_RE+"$"},{className:"meta",
begin:"\\*"+e.UNDERSCORE_IDENT_RE+"$"},{className:"bullet",begin:"-(?=[ ]|$)",
relevance:0},e.HASH_COMMENT_MODE,{beginKeywords:n,keywords:{literal:n}},{
className:"number",
begin:"\\b[0-9]{4}(-[0-9][0-9]){0,2}([Tt \\t][0-9][0-9]?(:[0-9][0-9]){2})?(\\.[0-9]*)?([ \\t])*(Z|[-+][0-9][0-9]?(:[0-9][0-9])?)?\\b"
},{className:"number",begin:e.C_NUMBER_RE+"\\b",relevance:0},i,o,t],l=[...c]
;return l.pop(),l.push(a),r.contains=l,{name:"YAML",case_insensitive:!0,
aliases:["yml"],contains:c}},grmr_dart:e=>{const n={className:"subst",
variants:[{begin:"\\$[A-Za-z0-9_]+"}]},s={className:"subst",variants:[{
begin:/\$\{/,end:/\}/}],keywords:"true false null this is new super"},t={
className:"string",variants:[{begin:"r'''",end:"'''"},{begin:'r"""',end:'"""'},{
begin:"r'",end:"'",illegal:"\\n"},{begin:'r"',end:'"',illegal:"\\n"},{
begin:"'''",end:"'''",contains:[e.BACKSLASH_ESCAPE,n,s]},{begin:'"""',end:'"""',
contains:[e.BACKSLASH_ESCAPE,n,s]},{begin:"'",end:"'",illegal:"\\n",
contains:[e.BACKSLASH_ESCAPE,n,s]},{begin:'"',end:'"',illegal:"\\n",
contains:[e.BACKSLASH_ESCAPE,n,s]}]};s.contains=[e.C_NUMBER_MODE,t]
;const a=["Comparable","DateTime","Duration","Function","Iterable","Iterator","List","Map","Match","Object","Pattern","RegExp","Set","Stopwatch","String","StringBuffer","StringSink","Symbol","Type","Uri","bool","double","int","num","Element","ElementList"],r=a.map((e=>e+"?"))
;return{name:"Dart",keywords:{
keyword:["abstract","as","assert","async","await","break","case","catch","class","const","continue","covariant","default","deferred","do","dynamic","else","enum","export","extends","extension","external","factory","false","final","finally","for","Function","get","hide","if","implements","import","in","inferface","is","late","library","mixin","new","null","on","operator","part","required","rethrow","return","set","show","static","super","switch","sync","this","throw","true","try","typedef","var","void","while","with","yield"],
built_in:a.concat(r).concat(["Never","Null","dynamic","print","document","querySelector","querySelectorAll","window"]),
$pattern:/[A-Za-z][A-Za-z0-9_]*\??/},
contains:[t,e.COMMENT(/\/\*\*(?!\/)/,/\*\//,{subLanguage:"markdown",relevance:0
}),e.COMMENT(/\/{3,} ?/,/$/,{contains:[{subLanguage:"markdown",begin:".",
end:"$",relevance:0}]}),e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE,{
className:"class",beginKeywords:"class interface",end:/\{/,excludeEnd:!0,
contains:[{beginKeywords:"extends implements"},e.UNDERSCORE_TITLE_MODE]
},e.C_NUMBER_MODE,{className:"meta",begin:"@[A-Za-z]+"},{begin:"=>"}]}},
grmr_dos:e=>{const n=e.COMMENT(/^\s*@?rem\b/,/$/,{relevance:10});return{
name:"Batch file (DOS)",aliases:["bat","cmd"],case_insensitive:!0,
illegal:/\/\*/,keywords:{
keyword:["if","else","goto","for","in","do","call","exit","not","exist","errorlevel","defined","equ","neq","lss","leq","gtr","geq"],
built_in:["prn","nul","lpt3","lpt2","lpt1","con","com4","com3","com2","com1","aux","shift","cd","dir","echo","setlocal","endlocal","set","pause","copy","append","assoc","at","attrib","break","cacls","cd","chcp","chdir","chkdsk","chkntfs","cls","cmd","color","comp","compact","convert","date","dir","diskcomp","diskcopy","doskey","erase","fs","find","findstr","format","ftype","graftabl","help","keyb","label","md","mkdir","mode","more","move","path","pause","print","popd","pushd","promt","rd","recover","rem","rename","replace","restore","rmdir","shift","sort","start","subst","time","title","tree","type","ver","verify","vol","ping","net","ipconfig","taskkill","xcopy","ren","del"]
},contains:[{className:"variable",begin:/%%[^ ]|%[^ ]+?%|![^ ]+?!/},{
className:"function",begin:"^\\s*[A-Za-z._?][A-Za-z0-9_$#@~.?]*(:|\\s+label)",
end:"goto:eof",contains:[e.inherit(e.TITLE_MODE,{
begin:"([_a-zA-Z]\\w*\\.)*([_a-zA-Z]\\w*:)?[_a-zA-Z]\\w*"}),n]},{
className:"number",begin:"\\b\\d+",relevance:0},n]}},grmr_armasm:e=>{const n={
variants:[e.COMMENT("^[ \\t]*(?=#)","$",{relevance:0,excludeBegin:!0
}),e.COMMENT("[;@]","$",{relevance:0
}),e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE]};return{name:"ARM Assembly",
case_insensitive:!0,aliases:["arm"],keywords:{$pattern:"\\.?"+e.IDENT_RE,
meta:".2byte .4byte .align .ascii .asciz .balign .byte .code .data .else .end .endif .endm .endr .equ .err .exitm .extern .global .hword .if .ifdef .ifndef .include .irp .long .macro .rept .req .section .set .skip .space .text .word .arm .thumb .code16 .code32 .force_thumb .thumb_func .ltorg ALIAS ALIGN ARM AREA ASSERT ATTR CN CODE CODE16 CODE32 COMMON CP DATA DCB DCD DCDU DCDO DCFD DCFDU DCI DCQ DCQU DCW DCWU DN ELIF ELSE END ENDFUNC ENDIF ENDP ENTRY EQU EXPORT EXPORTAS EXTERN FIELD FILL FUNCTION GBLA GBLL GBLS GET GLOBAL IF IMPORT INCBIN INCLUDE INFO KEEP LCLA LCLL LCLS LTORG MACRO MAP MEND MEXIT NOFP OPT PRESERVE8 PROC QN READONLY RELOC REQUIRE REQUIRE8 RLIST FN ROUT SETA SETL SETS SN SPACE SUBT THUMB THUMBX TTL WHILE WEND ",
built_in:"r0 r1 r2 r3 r4 r5 r6 r7 r8 r9 r10 r11 r12 r13 r14 r15 pc lr sp ip sl sb fp a1 a2 a3 a4 v1 v2 v3 v4 v5 v6 v7 v8 f0 f1 f2 f3 f4 f5 f6 f7 p0 p1 p2 p3 p4 p5 p6 p7 p8 p9 p10 p11 p12 p13 p14 p15 c0 c1 c2 c3 c4 c5 c6 c7 c8 c9 c10 c11 c12 c13 c14 c15 q0 q1 q2 q3 q4 q5 q6 q7 q8 q9 q10 q11 q12 q13 q14 q15 cpsr_c cpsr_x cpsr_s cpsr_f cpsr_cx cpsr_cxs cpsr_xs cpsr_xsf cpsr_sf cpsr_cxsf spsr_c spsr_x spsr_s spsr_f spsr_cx spsr_cxs spsr_xs spsr_xsf spsr_sf spsr_cxsf s0 s1 s2 s3 s4 s5 s6 s7 s8 s9 s10 s11 s12 s13 s14 s15 s16 s17 s18 s19 s20 s21 s22 s23 s24 s25 s26 s27 s28 s29 s30 s31 d0 d1 d2 d3 d4 d5 d6 d7 d8 d9 d10 d11 d12 d13 d14 d15 d16 d17 d18 d19 d20 d21 d22 d23 d24 d25 d26 d27 d28 d29 d30 d31 {PC} {VAR} {TRUE} {FALSE} {OPT} {CONFIG} {ENDIAN} {CODESIZE} {CPU} {FPU} {ARCHITECTURE} {PCSTOREOFFSET} {ARMASM_VERSION} {INTER} {ROPI} {RWPI} {SWST} {NOSWST} . @"
},contains:[{className:"keyword",
begin:"\\b(adc|(qd?|sh?|u[qh]?)?add(8|16)?|usada?8|(q|sh?|u[qh]?)?(as|sa)x|and|adrl?|sbc|rs[bc]|asr|b[lx]?|blx|bxj|cbn?z|tb[bh]|bic|bfc|bfi|[su]bfx|bkpt|cdp2?|clz|clrex|cmp|cmn|cpsi[ed]|cps|setend|dbg|dmb|dsb|eor|isb|it[te]{0,3}|lsl|lsr|ror|rrx|ldm(([id][ab])|f[ds])?|ldr((s|ex)?[bhd])?|movt?|mvn|mra|mar|mul|[us]mull|smul[bwt][bt]|smu[as]d|smmul|smmla|mla|umlaal|smlal?([wbt][bt]|d)|mls|smlsl?[ds]|smc|svc|sev|mia([bt]{2}|ph)?|mrr?c2?|mcrr2?|mrs|msr|orr|orn|pkh(tb|bt)|rbit|rev(16|sh)?|sel|[su]sat(16)?|nop|pop|push|rfe([id][ab])?|stm([id][ab])?|str(ex)?[bhd]?|(qd?)?sub|(sh?|q|u[qh]?)?sub(8|16)|[su]xt(a?h|a?b(16)?)|srs([id][ab])?|swpb?|swi|smi|tst|teq|wfe|wfi|yield)(eq|ne|cs|cc|mi|pl|vs|vc|hi|ls|ge|lt|gt|le|al|hs|lo)?[sptrx]?(?=\\s)"
},n,e.QUOTE_STRING_MODE,{className:"string",begin:"'",end:"[^\\\\]'",relevance:0
},{className:"title",begin:"\\|",end:"\\|",illegal:"\\n",relevance:0},{
className:"number",variants:[{begin:"[#$=]?0x[0-9a-f]+"},{begin:"[#$=]?0b[01]+"
},{begin:"[#$=]\\d+"},{begin:"\\b\\d+"}],relevance:0},{className:"symbol",
variants:[{begin:"^[ \\t]*[a-z_\\.\\$][a-z0-9_\\.\\$]+:"},{
begin:"^[a-z_\\.\\$][a-z0-9_\\.\\$]+"},{begin:"[=#]\\w+"}],relevance:0}]}},
grmr_avrasm:e=>({name:"AVR Assembly",case_insensitive:!0,keywords:{
$pattern:"\\.?"+e.IDENT_RE,
keyword:"adc add adiw and andi asr bclr bld brbc brbs brcc brcs break breq brge brhc brhs brid brie brlo brlt brmi brne brpl brsh brtc brts brvc brvs bset bst call cbi cbr clc clh cli cln clr cls clt clv clz com cp cpc cpi cpse dec eicall eijmp elpm eor fmul fmuls fmulsu icall ijmp in inc jmp ld ldd ldi lds lpm lsl lsr mov movw mul muls mulsu neg nop or ori out pop push rcall ret reti rjmp rol ror sbc sbr sbrc sbrs sec seh sbi sbci sbic sbis sbiw sei sen ser ses set sev sez sleep spm st std sts sub subi swap tst wdr",
built_in:"r0 r1 r2 r3 r4 r5 r6 r7 r8 r9 r10 r11 r12 r13 r14 r15 r16 r17 r18 r19 r20 r21 r22 r23 r24 r25 r26 r27 r28 r29 r30 r31 x|0 xh xl y|0 yh yl z|0 zh zl ucsr1c udr1 ucsr1a ucsr1b ubrr1l ubrr1h ucsr0c ubrr0h tccr3c tccr3a tccr3b tcnt3h tcnt3l ocr3ah ocr3al ocr3bh ocr3bl ocr3ch ocr3cl icr3h icr3l etimsk etifr tccr1c ocr1ch ocr1cl twcr twdr twar twsr twbr osccal xmcra xmcrb eicra spmcsr spmcr portg ddrg ping portf ddrf sreg sph spl xdiv rampz eicrb eimsk gimsk gicr eifr gifr timsk tifr mcucr mcucsr tccr0 tcnt0 ocr0 assr tccr1a tccr1b tcnt1h tcnt1l ocr1ah ocr1al ocr1bh ocr1bl icr1h icr1l tccr2 tcnt2 ocr2 ocdr wdtcr sfior eearh eearl eedr eecr porta ddra pina portb ddrb pinb portc ddrc pinc portd ddrd pind spdr spsr spcr udr0 ucsr0a ucsr0b ubrr0l acsr admux adcsr adch adcl porte ddre pine pinf",
meta:".byte .cseg .db .def .device .dseg .dw .endmacro .equ .eseg .exit .include .list .listmac .macro .nolist .org .set"
},contains:[e.C_BLOCK_COMMENT_MODE,e.COMMENT(";","$",{relevance:0
}),e.C_NUMBER_MODE,e.BINARY_NUMBER_MODE,{className:"number",
begin:"\\b(\\$[a-zA-Z0-9]+|0o[0-7]+)"},e.QUOTE_STRING_MODE,{className:"string",
begin:"'",end:"[^\\\\]'",illegal:"[^\\\\][^']"},{className:"symbol",
begin:"^[A-Za-z0-9_.$]+:"},{className:"meta",begin:"#",end:"$"},{
className:"subst",begin:"@[0-9]+"}]}),grmr_x86asm:e=>({
name:"Intel x86 Assembly",case_insensitive:!0,keywords:{
$pattern:"[.%]?"+e.IDENT_RE,
keyword:"lock rep repe repz repne repnz xaquire xrelease bnd nobnd aaa aad aam aas adc add and arpl bb0_reset bb1_reset bound bsf bsr bswap bt btc btr bts call cbw cdq cdqe clc cld cli clts cmc cmp cmpsb cmpsd cmpsq cmpsw cmpxchg cmpxchg486 cmpxchg8b cmpxchg16b cpuid cpu_read cpu_write cqo cwd cwde daa das dec div dmint emms enter equ f2xm1 fabs fadd faddp fbld fbstp fchs fclex fcmovb fcmovbe fcmove fcmovnb fcmovnbe fcmovne fcmovnu fcmovu fcom fcomi fcomip fcomp fcompp fcos fdecstp fdisi fdiv fdivp fdivr fdivrp femms feni ffree ffreep fiadd ficom ficomp fidiv fidivr fild fimul fincstp finit fist fistp fisttp fisub fisubr fld fld1 fldcw fldenv fldl2e fldl2t fldlg2 fldln2 fldpi fldz fmul fmulp fnclex fndisi fneni fninit fnop fnsave fnstcw fnstenv fnstsw fpatan fprem fprem1 fptan frndint frstor fsave fscale fsetpm fsin fsincos fsqrt fst fstcw fstenv fstp fstsw fsub fsubp fsubr fsubrp ftst fucom fucomi fucomip fucomp fucompp fxam fxch fxtract fyl2x fyl2xp1 hlt ibts icebp idiv imul in inc incbin insb insd insw int int01 int1 int03 int3 into invd invpcid invlpg invlpga iret iretd iretq iretw jcxz jecxz jrcxz jmp jmpe lahf lar lds lea leave les lfence lfs lgdt lgs lidt lldt lmsw loadall loadall286 lodsb lodsd lodsq lodsw loop loope loopne loopnz loopz lsl lss ltr mfence monitor mov movd movq movsb movsd movsq movsw movsx movsxd movzx mul mwait neg nop not or out outsb outsd outsw packssdw packsswb packuswb paddb paddd paddsb paddsiw paddsw paddusb paddusw paddw pand pandn pause paveb pavgusb pcmpeqb pcmpeqd pcmpeqw pcmpgtb pcmpgtd pcmpgtw pdistib pf2id pfacc pfadd pfcmpeq pfcmpge pfcmpgt pfmax pfmin pfmul pfrcp pfrcpit1 pfrcpit2 pfrsqit1 pfrsqrt pfsub pfsubr pi2fd pmachriw pmaddwd pmagw pmulhriw pmulhrwa pmulhrwc pmulhw pmullw pmvgezb pmvlzb pmvnzb pmvzb pop popa popad popaw popf popfd popfq popfw por prefetch prefetchw pslld psllq psllw psrad psraw psrld psrlq psrlw psubb psubd psubsb psubsiw psubsw psubusb psubusw psubw punpckhbw punpckhdq punpckhwd punpcklbw punpckldq punpcklwd push pusha pushad pushaw pushf pushfd pushfq pushfw pxor rcl rcr rdshr rdmsr rdpmc rdtsc rdtscp ret retf retn rol ror rdm rsdc rsldt rsm rsts sahf sal salc sar sbb scasb scasd scasq scasw sfence sgdt shl shld shr shrd sidt sldt skinit smi smint smintold smsw stc std sti stosb stosd stosq stosw str sub svdc svldt svts swapgs syscall sysenter sysexit sysret test ud0 ud1 ud2b ud2 ud2a umov verr verw fwait wbinvd wrshr wrmsr xadd xbts xchg xlatb xlat xor cmove cmovz cmovne cmovnz cmova cmovnbe cmovae cmovnb cmovb cmovnae cmovbe cmovna cmovg cmovnle cmovge cmovnl cmovl cmovnge cmovle cmovng cmovc cmovnc cmovo cmovno cmovs cmovns cmovp cmovpe cmovnp cmovpo je jz jne jnz ja jnbe jae jnb jb jnae jbe jna jg jnle jge jnl jl jnge jle jng jc jnc jo jno js jns jpo jnp jpe jp sete setz setne setnz seta setnbe setae setnb setnc setb setnae setcset setbe setna setg setnle setge setnl setl setnge setle setng sets setns seto setno setpe setp setpo setnp addps addss andnps andps cmpeqps cmpeqss cmpleps cmpless cmpltps cmpltss cmpneqps cmpneqss cmpnleps cmpnless cmpnltps cmpnltss cmpordps cmpordss cmpunordps cmpunordss cmpps cmpss comiss cvtpi2ps cvtps2pi cvtsi2ss cvtss2si cvttps2pi cvttss2si divps divss ldmxcsr maxps maxss minps minss movaps movhps movlhps movlps movhlps movmskps movntps movss movups mulps mulss orps rcpps rcpss rsqrtps rsqrtss shufps sqrtps sqrtss stmxcsr subps subss ucomiss unpckhps unpcklps xorps fxrstor fxrstor64 fxsave fxsave64 xgetbv xsetbv xsave xsave64 xsaveopt xsaveopt64 xrstor xrstor64 prefetchnta prefetcht0 prefetcht1 prefetcht2 maskmovq movntq pavgb pavgw pextrw pinsrw pmaxsw pmaxub pminsw pminub pmovmskb pmulhuw psadbw pshufw pf2iw pfnacc pfpnacc pi2fw pswapd maskmovdqu clflush movntdq movnti movntpd movdqa movdqu movdq2q movq2dq paddq pmuludq pshufd pshufhw pshuflw pslldq psrldq psubq punpckhqdq punpcklqdq addpd addsd andnpd andpd cmpeqpd cmpeqsd cmplepd cmplesd cmpltpd cmpltsd cmpneqpd cmpneqsd cmpnlepd cmpnlesd cmpnltpd cmpnltsd cmpordpd cmpordsd cmpunordpd cmpunordsd cmppd comisd cvtdq2pd cvtdq2ps cvtpd2dq cvtpd2pi cvtpd2ps cvtpi2pd cvtps2dq cvtps2pd cvtsd2si cvtsd2ss cvtsi2sd cvtss2sd cvttpd2pi cvttpd2dq cvttps2dq cvttsd2si divpd divsd maxpd maxsd minpd minsd movapd movhpd movlpd movmskpd movupd mulpd mulsd orpd shufpd sqrtpd sqrtsd subpd subsd ucomisd unpckhpd unpcklpd xorpd addsubpd addsubps haddpd haddps hsubpd hsubps lddqu movddup movshdup movsldup clgi stgi vmcall vmclear vmfunc vmlaunch vmload vmmcall vmptrld vmptrst vmread vmresume vmrun vmsave vmwrite vmxoff vmxon invept invvpid pabsb pabsw pabsd palignr phaddw phaddd phaddsw phsubw phsubd phsubsw pmaddubsw pmulhrsw pshufb psignb psignw psignd extrq insertq movntsd movntss lzcnt blendpd blendps blendvpd blendvps dppd dpps extractps insertps movntdqa mpsadbw packusdw pblendvb pblendw pcmpeqq pextrb pextrd pextrq phminposuw pinsrb pinsrd pinsrq pmaxsb pmaxsd pmaxud pmaxuw pminsb pminsd pminud pminuw pmovsxbw pmovsxbd pmovsxbq pmovsxwd pmovsxwq pmovsxdq pmovzxbw pmovzxbd pmovzxbq pmovzxwd pmovzxwq pmovzxdq pmuldq pmulld ptest roundpd roundps roundsd roundss crc32 pcmpestri pcmpestrm pcmpistri pcmpistrm pcmpgtq popcnt getsec pfrcpv pfrsqrtv movbe aesenc aesenclast aesdec aesdeclast aesimc aeskeygenassist vaesenc vaesenclast vaesdec vaesdeclast vaesimc vaeskeygenassist vaddpd vaddps vaddsd vaddss vaddsubpd vaddsubps vandpd vandps vandnpd vandnps vblendpd vblendps vblendvpd vblendvps vbroadcastss vbroadcastsd vbroadcastf128 vcmpeq_ospd vcmpeqpd vcmplt_ospd vcmpltpd vcmple_ospd vcmplepd vcmpunord_qpd vcmpunordpd vcmpneq_uqpd vcmpneqpd vcmpnlt_uspd vcmpnltpd vcmpnle_uspd vcmpnlepd vcmpord_qpd vcmpordpd vcmpeq_uqpd vcmpnge_uspd vcmpngepd vcmpngt_uspd vcmpngtpd vcmpfalse_oqpd vcmpfalsepd vcmpneq_oqpd vcmpge_ospd vcmpgepd vcmpgt_ospd vcmpgtpd vcmptrue_uqpd vcmptruepd vcmplt_oqpd vcmple_oqpd vcmpunord_spd vcmpneq_uspd vcmpnlt_uqpd vcmpnle_uqpd vcmpord_spd vcmpeq_uspd vcmpnge_uqpd vcmpngt_uqpd vcmpfalse_ospd vcmpneq_ospd vcmpge_oqpd vcmpgt_oqpd vcmptrue_uspd vcmppd vcmpeq_osps vcmpeqps vcmplt_osps vcmpltps vcmple_osps vcmpleps vcmpunord_qps vcmpunordps vcmpneq_uqps vcmpneqps vcmpnlt_usps vcmpnltps vcmpnle_usps vcmpnleps vcmpord_qps vcmpordps vcmpeq_uqps vcmpnge_usps vcmpngeps vcmpngt_usps vcmpngtps vcmpfalse_oqps vcmpfalseps vcmpneq_oqps vcmpge_osps vcmpgeps vcmpgt_osps vcmpgtps vcmptrue_uqps vcmptrueps vcmplt_oqps vcmple_oqps vcmpunord_sps vcmpneq_usps vcmpnlt_uqps vcmpnle_uqps vcmpord_sps vcmpeq_usps vcmpnge_uqps vcmpngt_uqps vcmpfalse_osps vcmpneq_osps vcmpge_oqps vcmpgt_oqps vcmptrue_usps vcmpps vcmpeq_ossd vcmpeqsd vcmplt_ossd vcmpltsd vcmple_ossd vcmplesd vcmpunord_qsd vcmpunordsd vcmpneq_uqsd vcmpneqsd vcmpnlt_ussd vcmpnltsd vcmpnle_ussd vcmpnlesd vcmpord_qsd vcmpordsd vcmpeq_uqsd vcmpnge_ussd vcmpngesd vcmpngt_ussd vcmpngtsd vcmpfalse_oqsd vcmpfalsesd vcmpneq_oqsd vcmpge_ossd vcmpgesd vcmpgt_ossd vcmpgtsd vcmptrue_uqsd vcmptruesd vcmplt_oqsd vcmple_oqsd vcmpunord_ssd vcmpneq_ussd vcmpnlt_uqsd vcmpnle_uqsd vcmpord_ssd vcmpeq_ussd vcmpnge_uqsd vcmpngt_uqsd vcmpfalse_ossd vcmpneq_ossd vcmpge_oqsd vcmpgt_oqsd vcmptrue_ussd vcmpsd vcmpeq_osss vcmpeqss vcmplt_osss vcmpltss vcmple_osss vcmpless vcmpunord_qss vcmpunordss vcmpneq_uqss vcmpneqss vcmpnlt_usss vcmpnltss vcmpnle_usss vcmpnless vcmpord_qss vcmpordss vcmpeq_uqss vcmpnge_usss vcmpngess vcmpngt_usss vcmpngtss vcmpfalse_oqss vcmpfalsess vcmpneq_oqss vcmpge_osss vcmpgess vcmpgt_osss vcmpgtss vcmptrue_uqss vcmptruess vcmplt_oqss vcmple_oqss vcmpunord_sss vcmpneq_usss vcmpnlt_uqss vcmpnle_uqss vcmpord_sss vcmpeq_usss vcmpnge_uqss vcmpngt_uqss vcmpfalse_osss vcmpneq_osss vcmpge_oqss vcmpgt_oqss vcmptrue_usss vcmpss vcomisd vcomiss vcvtdq2pd vcvtdq2ps vcvtpd2dq vcvtpd2ps vcvtps2dq vcvtps2pd vcvtsd2si vcvtsd2ss vcvtsi2sd vcvtsi2ss vcvtss2sd vcvtss2si vcvttpd2dq vcvttps2dq vcvttsd2si vcvttss2si vdivpd vdivps vdivsd vdivss vdppd vdpps vextractf128 vextractps vhaddpd vhaddps vhsubpd vhsubps vinsertf128 vinsertps vlddqu vldqqu vldmxcsr vmaskmovdqu vmaskmovps vmaskmovpd vmaxpd vmaxps vmaxsd vmaxss vminpd vminps vminsd vminss vmovapd vmovaps vmovd vmovq vmovddup vmovdqa vmovqqa vmovdqu vmovqqu vmovhlps vmovhpd vmovhps vmovlhps vmovlpd vmovlps vmovmskpd vmovmskps vmovntdq vmovntqq vmovntdqa vmovntpd vmovntps vmovsd vmovshdup vmovsldup vmovss vmovupd vmovups vmpsadbw vmulpd vmulps vmulsd vmulss vorpd vorps vpabsb vpabsw vpabsd vpacksswb vpackssdw vpackuswb vpackusdw vpaddb vpaddw vpaddd vpaddq vpaddsb vpaddsw vpaddusb vpaddusw vpalignr vpand vpandn vpavgb vpavgw vpblendvb vpblendw vpcmpestri vpcmpestrm vpcmpistri vpcmpistrm vpcmpeqb vpcmpeqw vpcmpeqd vpcmpeqq vpcmpgtb vpcmpgtw vpcmpgtd vpcmpgtq vpermilpd vpermilps vperm2f128 vpextrb vpextrw vpextrd vpextrq vphaddw vphaddd vphaddsw vphminposuw vphsubw vphsubd vphsubsw vpinsrb vpinsrw vpinsrd vpinsrq vpmaddwd vpmaddubsw vpmaxsb vpmaxsw vpmaxsd vpmaxub vpmaxuw vpmaxud vpminsb vpminsw vpminsd vpminub vpminuw vpminud vpmovmskb vpmovsxbw vpmovsxbd vpmovsxbq vpmovsxwd vpmovsxwq vpmovsxdq vpmovzxbw vpmovzxbd vpmovzxbq vpmovzxwd vpmovzxwq vpmovzxdq vpmulhuw vpmulhrsw vpmulhw vpmullw vpmulld vpmuludq vpmuldq vpor vpsadbw vpshufb vpshufd vpshufhw vpshuflw vpsignb vpsignw vpsignd vpslldq vpsrldq vpsllw vpslld vpsllq vpsraw vpsrad vpsrlw vpsrld vpsrlq vptest vpsubb vpsubw vpsubd vpsubq vpsubsb vpsubsw vpsubusb vpsubusw vpunpckhbw vpunpckhwd vpunpckhdq vpunpckhqdq vpunpcklbw vpunpcklwd vpunpckldq vpunpcklqdq vpxor vrcpps vrcpss vrsqrtps vrsqrtss vroundpd vroundps vroundsd vroundss vshufpd vshufps vsqrtpd vsqrtps vsqrtsd vsqrtss vstmxcsr vsubpd vsubps vsubsd vsubss vtestps vtestpd vucomisd vucomiss vunpckhpd vunpckhps vunpcklpd vunpcklps vxorpd vxorps vzeroall vzeroupper pclmullqlqdq pclmulhqlqdq pclmullqhqdq pclmulhqhqdq pclmulqdq vpclmullqlqdq vpclmulhqlqdq vpclmullqhqdq vpclmulhqhqdq vpclmulqdq vfmadd132ps vfmadd132pd vfmadd312ps vfmadd312pd vfmadd213ps vfmadd213pd vfmadd123ps vfmadd123pd vfmadd231ps vfmadd231pd vfmadd321ps vfmadd321pd vfmaddsub132ps vfmaddsub132pd vfmaddsub312ps vfmaddsub312pd vfmaddsub213ps vfmaddsub213pd vfmaddsub123ps vfmaddsub123pd vfmaddsub231ps vfmaddsub231pd vfmaddsub321ps vfmaddsub321pd vfmsub132ps vfmsub132pd vfmsub312ps vfmsub312pd vfmsub213ps vfmsub213pd vfmsub123ps vfmsub123pd vfmsub231ps vfmsub231pd vfmsub321ps vfmsub321pd vfmsubadd132ps vfmsubadd132pd vfmsubadd312ps vfmsubadd312pd vfmsubadd213ps vfmsubadd213pd vfmsubadd123ps vfmsubadd123pd vfmsubadd231ps vfmsubadd231pd vfmsubadd321ps vfmsubadd321pd vfnmadd132ps vfnmadd132pd vfnmadd312ps vfnmadd312pd vfnmadd213ps vfnmadd213pd vfnmadd123ps vfnmadd123pd vfnmadd231ps vfnmadd231pd vfnmadd321ps vfnmadd321pd vfnmsub132ps vfnmsub132pd vfnmsub312ps vfnmsub312pd vfnmsub213ps vfnmsub213pd vfnmsub123ps vfnmsub123pd vfnmsub231ps vfnmsub231pd vfnmsub321ps vfnmsub321pd vfmadd132ss vfmadd132sd vfmadd312ss vfmadd312sd vfmadd213ss vfmadd213sd vfmadd123ss vfmadd123sd vfmadd231ss vfmadd231sd vfmadd321ss vfmadd321sd vfmsub132ss vfmsub132sd vfmsub312ss vfmsub312sd vfmsub213ss vfmsub213sd vfmsub123ss vfmsub123sd vfmsub231ss vfmsub231sd vfmsub321ss vfmsub321sd vfnmadd132ss vfnmadd132sd vfnmadd312ss vfnmadd312sd vfnmadd213ss vfnmadd213sd vfnmadd123ss vfnmadd123sd vfnmadd231ss vfnmadd231sd vfnmadd321ss vfnmadd321sd vfnmsub132ss vfnmsub132sd vfnmsub312ss vfnmsub312sd vfnmsub213ss vfnmsub213sd vfnmsub123ss vfnmsub123sd vfnmsub231ss vfnmsub231sd vfnmsub321ss vfnmsub321sd rdfsbase rdgsbase rdrand wrfsbase wrgsbase vcvtph2ps vcvtps2ph adcx adox rdseed clac stac xstore xcryptecb xcryptcbc xcryptctr xcryptcfb xcryptofb montmul xsha1 xsha256 llwpcb slwpcb lwpval lwpins vfmaddpd vfmaddps vfmaddsd vfmaddss vfmaddsubpd vfmaddsubps vfmsubaddpd vfmsubaddps vfmsubpd vfmsubps vfmsubsd vfmsubss vfnmaddpd vfnmaddps vfnmaddsd vfnmaddss vfnmsubpd vfnmsubps vfnmsubsd vfnmsubss vfrczpd vfrczps vfrczsd vfrczss vpcmov vpcomb vpcomd vpcomq vpcomub vpcomud vpcomuq vpcomuw vpcomw vphaddbd vphaddbq vphaddbw vphadddq vphaddubd vphaddubq vphaddubw vphaddudq vphadduwd vphadduwq vphaddwd vphaddwq vphsubbw vphsubdq vphsubwd vpmacsdd vpmacsdqh vpmacsdql vpmacssdd vpmacssdqh vpmacssdql vpmacsswd vpmacssww vpmacswd vpmacsww vpmadcsswd vpmadcswd vpperm vprotb vprotd vprotq vprotw vpshab vpshad vpshaq vpshaw vpshlb vpshld vpshlq vpshlw vbroadcasti128 vpblendd vpbroadcastb vpbroadcastw vpbroadcastd vpbroadcastq vpermd vpermpd vpermps vpermq vperm2i128 vextracti128 vinserti128 vpmaskmovd vpmaskmovq vpsllvd vpsllvq vpsravd vpsrlvd vpsrlvq vgatherdpd vgatherqpd vgatherdps vgatherqps vpgatherdd vpgatherqd vpgatherdq vpgatherqq xabort xbegin xend xtest andn bextr blci blcic blsi blsic blcfill blsfill blcmsk blsmsk blsr blcs bzhi mulx pdep pext rorx sarx shlx shrx tzcnt tzmsk t1mskc valignd valignq vblendmpd vblendmps vbroadcastf32x4 vbroadcastf64x4 vbroadcasti32x4 vbroadcasti64x4 vcompresspd vcompressps vcvtpd2udq vcvtps2udq vcvtsd2usi vcvtss2usi vcvttpd2udq vcvttps2udq vcvttsd2usi vcvttss2usi vcvtudq2pd vcvtudq2ps vcvtusi2sd vcvtusi2ss vexpandpd vexpandps vextractf32x4 vextractf64x4 vextracti32x4 vextracti64x4 vfixupimmpd vfixupimmps vfixupimmsd vfixupimmss vgetexppd vgetexpps vgetexpsd vgetexpss vgetmantpd vgetmantps vgetmantsd vgetmantss vinsertf32x4 vinsertf64x4 vinserti32x4 vinserti64x4 vmovdqa32 vmovdqa64 vmovdqu32 vmovdqu64 vpabsq vpandd vpandnd vpandnq vpandq vpblendmd vpblendmq vpcmpltd vpcmpled vpcmpneqd vpcmpnltd vpcmpnled vpcmpd vpcmpltq vpcmpleq vpcmpneqq vpcmpnltq vpcmpnleq vpcmpq vpcmpequd vpcmpltud vpcmpleud vpcmpnequd vpcmpnltud vpcmpnleud vpcmpud vpcmpequq vpcmpltuq vpcmpleuq vpcmpnequq vpcmpnltuq vpcmpnleuq vpcmpuq vpcompressd vpcompressq vpermi2d vpermi2pd vpermi2ps vpermi2q vpermt2d vpermt2pd vpermt2ps vpermt2q vpexpandd vpexpandq vpmaxsq vpmaxuq vpminsq vpminuq vpmovdb vpmovdw vpmovqb vpmovqd vpmovqw vpmovsdb vpmovsdw vpmovsqb vpmovsqd vpmovsqw vpmovusdb vpmovusdw vpmovusqb vpmovusqd vpmovusqw vpord vporq vprold vprolq vprolvd vprolvq vprord vprorq vprorvd vprorvq vpscatterdd vpscatterdq vpscatterqd vpscatterqq vpsraq vpsravq vpternlogd vpternlogq vptestmd vptestmq vptestnmd vptestnmq vpxord vpxorq vrcp14pd vrcp14ps vrcp14sd vrcp14ss vrndscalepd vrndscaleps vrndscalesd vrndscaless vrsqrt14pd vrsqrt14ps vrsqrt14sd vrsqrt14ss vscalefpd vscalefps vscalefsd vscalefss vscatterdpd vscatterdps vscatterqpd vscatterqps vshuff32x4 vshuff64x2 vshufi32x4 vshufi64x2 kandnw kandw kmovw knotw kortestw korw kshiftlw kshiftrw kunpckbw kxnorw kxorw vpbroadcastmb2q vpbroadcastmw2d vpconflictd vpconflictq vplzcntd vplzcntq vexp2pd vexp2ps vrcp28pd vrcp28ps vrcp28sd vrcp28ss vrsqrt28pd vrsqrt28ps vrsqrt28sd vrsqrt28ss vgatherpf0dpd vgatherpf0dps vgatherpf0qpd vgatherpf0qps vgatherpf1dpd vgatherpf1dps vgatherpf1qpd vgatherpf1qps vscatterpf0dpd vscatterpf0dps vscatterpf0qpd vscatterpf0qps vscatterpf1dpd vscatterpf1dps vscatterpf1qpd vscatterpf1qps prefetchwt1 bndmk bndcl bndcu bndcn bndmov bndldx bndstx sha1rnds4 sha1nexte sha1msg1 sha1msg2 sha256rnds2 sha256msg1 sha256msg2 hint_nop0 hint_nop1 hint_nop2 hint_nop3 hint_nop4 hint_nop5 hint_nop6 hint_nop7 hint_nop8 hint_nop9 hint_nop10 hint_nop11 hint_nop12 hint_nop13 hint_nop14 hint_nop15 hint_nop16 hint_nop17 hint_nop18 hint_nop19 hint_nop20 hint_nop21 hint_nop22 hint_nop23 hint_nop24 hint_nop25 hint_nop26 hint_nop27 hint_nop28 hint_nop29 hint_nop30 hint_nop31 hint_nop32 hint_nop33 hint_nop34 hint_nop35 hint_nop36 hint_nop37 hint_nop38 hint_nop39 hint_nop40 hint_nop41 hint_nop42 hint_nop43 hint_nop44 hint_nop45 hint_nop46 hint_nop47 hint_nop48 hint_nop49 hint_nop50 hint_nop51 hint_nop52 hint_nop53 hint_nop54 hint_nop55 hint_nop56 hint_nop57 hint_nop58 hint_nop59 hint_nop60 hint_nop61 hint_nop62 hint_nop63",
built_in:"ip eip rip al ah bl bh cl ch dl dh sil dil bpl spl r8b r9b r10b r11b r12b r13b r14b r15b ax bx cx dx si di bp sp r8w r9w r10w r11w r12w r13w r14w r15w eax ebx ecx edx esi edi ebp esp eip r8d r9d r10d r11d r12d r13d r14d r15d rax rbx rcx rdx rsi rdi rbp rsp r8 r9 r10 r11 r12 r13 r14 r15 cs ds es fs gs ss st st0 st1 st2 st3 st4 st5 st6 st7 mm0 mm1 mm2 mm3 mm4 mm5 mm6 mm7 xmm0  xmm1  xmm2  xmm3  xmm4  xmm5  xmm6  xmm7  xmm8  xmm9 xmm10  xmm11 xmm12 xmm13 xmm14 xmm15 xmm16 xmm17 xmm18 xmm19 xmm20 xmm21 xmm22 xmm23 xmm24 xmm25 xmm26 xmm27 xmm28 xmm29 xmm30 xmm31 ymm0  ymm1  ymm2  ymm3  ymm4  ymm5  ymm6  ymm7  ymm8  ymm9 ymm10  ymm11 ymm12 ymm13 ymm14 ymm15 ymm16 ymm17 ymm18 ymm19 ymm20 ymm21 ymm22 ymm23 ymm24 ymm25 ymm26 ymm27 ymm28 ymm29 ymm30 ymm31 zmm0  zmm1  zmm2  zmm3  zmm4  zmm5  zmm6  zmm7  zmm8  zmm9 zmm10  zmm11 zmm12 zmm13 zmm14 zmm15 zmm16 zmm17 zmm18 zmm19 zmm20 zmm21 zmm22 zmm23 zmm24 zmm25 zmm26 zmm27 zmm28 zmm29 zmm30 zmm31 k0 k1 k2 k3 k4 k5 k6 k7 bnd0 bnd1 bnd2 bnd3 cr0 cr1 cr2 cr3 cr4 cr8 dr0 dr1 dr2 dr3 dr8 tr3 tr4 tr5 tr6 tr7 r0 r1 r2 r3 r4 r5 r6 r7 r0b r1b r2b r3b r4b r5b r6b r7b r0w r1w r2w r3w r4w r5w r6w r7w r0d r1d r2d r3d r4d r5d r6d r7d r0h r1h r2h r3h r0l r1l r2l r3l r4l r5l r6l r7l r8l r9l r10l r11l r12l r13l r14l r15l db dw dd dq dt ddq do dy dz resb resw resd resq rest resdq reso resy resz incbin equ times byte word dword qword nosplit rel abs seg wrt strict near far a32 ptr",
meta:"%define %xdefine %+ %undef %defstr %deftok %assign %strcat %strlen %substr %rotate %elif %else %endif %if %ifmacro %ifctx %ifidn %ifidni %ifid %ifnum %ifstr %iftoken %ifempty %ifenv %error %warning %fatal %rep %endrep %include %push %pop %repl %pathsearch %depend %use %arg %stacksize %local %line %comment %endcomment .nolist __FILE__ __LINE__ __SECT__  __BITS__ __OUTPUT_FORMAT__ __DATE__ __TIME__ __DATE_NUM__ __TIME_NUM__ __UTC_DATE__ __UTC_TIME__ __UTC_DATE_NUM__ __UTC_TIME_NUM__  __PASS__ struc endstruc istruc at iend align alignb sectalign daz nodaz up down zero default option assume public bits use16 use32 use64 default section segment absolute extern global common cpu float __utf16__ __utf16le__ __utf16be__ __utf32__ __utf32le__ __utf32be__ __float8__ __float16__ __float32__ __float64__ __float80m__ __float80e__ __float128l__ __float128h__ __Infinity__ __QNaN__ __SNaN__ Inf NaN QNaN SNaN float8 float16 float32 float64 float80m float80e float128l float128h __FLOAT_DAZ__ __FLOAT_ROUND__ __FLOAT__"
},contains:[e.COMMENT(";","$",{relevance:0}),{className:"number",variants:[{
begin:"\\b(?:([0-9][0-9_]*)?\\.[0-9_]*(?:[eE][+-]?[0-9_]+)?|(0[Xx])?[0-9][0-9_]*(\\.[0-9_]*)?(?:[pP](?:[+-]?[0-9_]+)?)?)\\b",
relevance:0},{begin:"\\$[0-9][0-9A-Fa-f]*",relevance:0},{
begin:"\\b(?:[0-9A-Fa-f][0-9A-Fa-f_]*[Hh]|[0-9][0-9_]*[DdTt]?|[0-7][0-7_]*[QqOo]|[0-1][0-1_]*[BbYy])\\b"
},{
begin:"\\b(?:0[Xx][0-9A-Fa-f_]+|0[DdTt][0-9_]+|0[QqOo][0-7_]+|0[BbYy][0-1_]+)\\b"
}]},e.QUOTE_STRING_MODE,{className:"string",variants:[{begin:"'",end:"[^\\\\]'"
},{begin:"`",end:"[^\\\\]`"}],relevance:0},{className:"symbol",variants:[{
begin:"^\\s*[A-Za-z._?][A-Za-z0-9_$#@~.?]*(:|\\s+label)"},{
begin:"^\\s*%%[A-Za-z0-9_$#@~.?]*:"}],relevance:0},{className:"subst",
begin:"%[0-9]+",relevance:0},{className:"subst",begin:"%!S+",relevance:0},{
className:"meta",begin:/^\s*\.[\w_-]+/}]}),grmr_mipsasm:e=>({
name:"MIPS Assembly",case_insensitive:!0,aliases:["mips"],keywords:{
$pattern:"\\.?"+e.IDENT_RE,
meta:".2byte .4byte .align .ascii .asciz .balign .byte .code .data .else .end .endif .endm .endr .equ .err .exitm .extern .global .hword .if .ifdef .ifndef .include .irp .long .macro .rept .req .section .set .skip .space .text .word .ltorg ",
built_in:"$0 $1 $2 $3 $4 $5 $6 $7 $8 $9 $10 $11 $12 $13 $14 $15 $16 $17 $18 $19 $20 $21 $22 $23 $24 $25 $26 $27 $28 $29 $30 $31 zero at v0 v1 a0 a1 a2 a3 a4 a5 a6 a7 t0 t1 t2 t3 t4 t5 t6 t7 t8 t9 s0 s1 s2 s3 s4 s5 s6 s7 s8 k0 k1 gp sp fp ra $f0 $f1 $f2 $f2 $f4 $f5 $f6 $f7 $f8 $f9 $f10 $f11 $f12 $f13 $f14 $f15 $f16 $f17 $f18 $f19 $f20 $f21 $f22 $f23 $f24 $f25 $f26 $f27 $f28 $f29 $f30 $f31 Context Random EntryLo0 EntryLo1 Context PageMask Wired EntryHi HWREna BadVAddr Count Compare SR IntCtl SRSCtl SRSMap Cause EPC PRId EBase Config Config1 Config2 Config3 LLAddr Debug DEPC DESAVE CacheErr ECC ErrorEPC TagLo DataLo TagHi DataHi WatchLo WatchHi PerfCtl PerfCnt "
},contains:[{className:"keyword",
begin:"\\b(addi?u?|andi?|b(al)?|beql?|bgez(al)?l?|bgtzl?|blezl?|bltz(al)?l?|bnel?|cl[oz]|divu?|ext|ins|j(al)?|jalr(\\.hb)?|jr(\\.hb)?|lbu?|lhu?|ll|lui|lw[lr]?|maddu?|mfhi|mflo|movn|movz|move|msubu?|mthi|mtlo|mul|multu?|nop|nor|ori?|rotrv?|sb|sc|se[bh]|sh|sllv?|slti?u?|srav?|srlv?|subu?|sw[lr]?|xori?|wsbh|abs\\.[sd]|add\\.[sd]|alnv.ps|bc1[ft]l?|c\\.(s?f|un|u?eq|[ou]lt|[ou]le|ngle?|seq|l[et]|ng[et])\\.[sd]|(ceil|floor|round|trunc)\\.[lw]\\.[sd]|cfc1|cvt\\.d\\.[lsw]|cvt\\.l\\.[dsw]|cvt\\.ps\\.s|cvt\\.s\\.[dlw]|cvt\\.s\\.p[lu]|cvt\\.w\\.[dls]|div\\.[ds]|ldx?c1|luxc1|lwx?c1|madd\\.[sd]|mfc1|mov[fntz]?\\.[ds]|msub\\.[sd]|mth?c1|mul\\.[ds]|neg\\.[ds]|nmadd\\.[ds]|nmsub\\.[ds]|p[lu][lu]\\.ps|recip\\.fmt|r?sqrt\\.[ds]|sdx?c1|sub\\.[ds]|suxc1|swx?c1|break|cache|d?eret|[de]i|ehb|mfc0|mtc0|pause|prefx?|rdhwr|rdpgpr|sdbbp|ssnop|synci?|syscall|teqi?|tgei?u?|tlb(p|r|w[ir])|tlti?u?|tnei?|wait|wrpgpr)",
end:"\\s"
},e.COMMENT("[;#](?!\\s*$)","$"),e.C_BLOCK_COMMENT_MODE,e.QUOTE_STRING_MODE,{
className:"string",begin:"'",end:"[^\\\\]'",relevance:0},{className:"title",
begin:"\\|",end:"\\|",illegal:"\\n",relevance:0},{className:"number",variants:[{
begin:"0x[0-9a-f]+"},{begin:"\\b-?\\d+"}],relevance:0},{className:"symbol",
variants:[{begin:"^\\s*[a-z_\\.\\$][a-z0-9_\\.\\$]+:"},{begin:"^\\s*[0-9]+:"},{
begin:"[0-9]+[bf]"}],relevance:0}],illegal:/\//}),grmr_basic:e=>({name:"BASIC",
case_insensitive:!0,illegal:"^.",keywords:{$pattern:"[a-zA-Z][a-zA-Z0-9_$%!#]*",
keyword:["ABS","ASC","AND","ATN","AUTO|0","BEEP","BLOAD|10","BSAVE|10","CALL","CALLS","CDBL","CHAIN","CHDIR","CHR$|10","CINT","CIRCLE","CLEAR","CLOSE","CLS","COLOR","COM","COMMON","CONT","COS","CSNG","CSRLIN","CVD","CVI","CVS","DATA","DATE$","DEFDBL","DEFINT","DEFSNG","DEFSTR","DEF|0","SEG","USR","DELETE","DIM","DRAW","EDIT","END","ENVIRON","ENVIRON$","EOF","EQV","ERASE","ERDEV","ERDEV$","ERL","ERR","ERROR","EXP","FIELD","FILES","FIX","FOR|0","FRE","GET","GOSUB|10","GOTO","HEX$","IF","THEN","ELSE|0","INKEY$","INP","INPUT","INPUT#","INPUT$","INSTR","IMP","INT","IOCTL","IOCTL$","KEY","ON","OFF","LIST","KILL","LEFT$","LEN","LET","LINE","LLIST","LOAD","LOC","LOCATE","LOF","LOG","LPRINT","USING","LSET","MERGE","MID$","MKDIR","MKD$","MKI$","MKS$","MOD","NAME","NEW","NEXT","NOISE","NOT","OCT$","ON","OR","PEN","PLAY","STRIG","OPEN","OPTION","BASE","OUT","PAINT","PALETTE","PCOPY","PEEK","PMAP","POINT","POKE","POS","PRINT","PRINT]","PSET","PRESET","PUT","RANDOMIZE","READ","REM","RENUM","RESET|0","RESTORE","RESUME","RETURN|0","RIGHT$","RMDIR","RND","RSET","RUN","SAVE","SCREEN","SGN","SHELL","SIN","SOUND","SPACE$","SPC","SQR","STEP","STICK","STOP","STR$","STRING$","SWAP","SYSTEM","TAB","TAN","TIME$","TIMER","TROFF","TRON","TO","USR","VAL","VARPTR","VARPTR$","VIEW","WAIT","WHILE","WEND","WIDTH","WINDOW","WRITE","XOR"]
},contains:[e.QUOTE_STRING_MODE,e.COMMENT("REM","$",{relevance:10
}),e.COMMENT("'","$",{relevance:0}),{className:"symbol",begin:"^[0-9]+ ",
relevance:10},{className:"number",begin:"\\b\\d+(\\.\\d+)?([edED]\\d+)?[#!]?",
relevance:0},{className:"number",begin:"(&[hH][0-9a-fA-F]{1,4})"},{
className:"number",begin:"(&[oO][0-7]{1,6})"}]}),grmr_cmake:e=>({name:"CMake",
aliases:["cmake.in"],case_insensitive:!0,keywords:{
keyword:"break cmake_host_system_information cmake_minimum_required cmake_parse_arguments cmake_policy configure_file continue elseif else endforeach endfunction endif endmacro endwhile execute_process file find_file find_library find_package find_path find_program foreach function get_cmake_property get_directory_property get_filename_component get_property if include include_guard list macro mark_as_advanced math message option return separate_arguments set_directory_properties set_property set site_name string unset variable_watch while add_compile_definitions add_compile_options add_custom_command add_custom_target add_definitions add_dependencies add_executable add_library add_link_options add_subdirectory add_test aux_source_directory build_command create_test_sourcelist define_property enable_language enable_testing export fltk_wrap_ui get_source_file_property get_target_property get_test_property include_directories include_external_msproject include_regular_expression install link_directories link_libraries load_cache project qt_wrap_cpp qt_wrap_ui remove_definitions set_source_files_properties set_target_properties set_tests_properties source_group target_compile_definitions target_compile_features target_compile_options target_include_directories target_link_directories target_link_libraries target_link_options target_sources try_compile try_run ctest_build ctest_configure ctest_coverage ctest_empty_binary_directory ctest_memcheck ctest_read_custom_files ctest_run_script ctest_sleep ctest_start ctest_submit ctest_test ctest_update ctest_upload build_name exec_program export_library_dependencies install_files install_programs install_targets load_command make_directory output_required_files remove subdir_depends subdirs use_mangled_mesa utility_source variable_requires write_file qt5_use_modules qt5_use_package qt5_wrap_cpp on off true false and or not command policy target test exists is_newer_than is_directory is_symlink is_absolute matches less greater equal less_equal greater_equal strless strgreater strequal strless_equal strgreater_equal version_less version_greater version_equal version_less_equal version_greater_equal in_list defined"
},contains:[{className:"variable",begin:/\$\{/,end:/\}/
},e.HASH_COMMENT_MODE,e.QUOTE_STRING_MODE,e.NUMBER_MODE]}),grmr_delphi:e=>{
const n=["exports","register","file","shl","array","record","property","for","mod","while","set","ally","label","uses","raise","not","stored","class","safecall","var","interface","or","private","static","exit","index","inherited","to","else","stdcall","override","shr","asm","far","resourcestring","finalization","packed","virtual","out","and","protected","library","do","xorwrite","goto","near","function","end","div","overload","object","unit","begin","string","on","inline","repeat","until","destructor","write","message","program","with","read","initialization","except","default","nil","if","case","cdecl","in","downto","threadvar","of","try","pascal","const","external","constructor","type","public","then","implementation","finally","published","procedure","absolute","reintroduce","operator","as","is","abstract","alias","assembler","bitpacked","break","continue","cppdecl","cvar","enumerator","experimental","platform","deprecated","unimplemented","dynamic","export","far16","forward","generic","helper","implements","interrupt","iochecks","local","name","nodefault","noreturn","nostackframe","oldfpccall","otherwise","saveregisters","softfloat","specialize","strict","unaligned","varargs"],s=[e.C_LINE_COMMENT_MODE,e.COMMENT(/\{/,/\}/,{
relevance:0}),e.COMMENT(/\(\*/,/\*\)/,{relevance:10})],t={className:"meta",
variants:[{begin:/\{\$/,end:/\}/},{begin:/\(\*\$/,end:/\*\)/}]},a={
className:"string",begin:/'/,end:/'/,contains:[{begin:/''/}]},r={
className:"string",begin:/(#\d+)+/},i={begin:e.IDENT_RE+"\\s*=\\s*class\\s*\\(",
returnBegin:!0,contains:[e.TITLE_MODE]},o={className:"function",
beginKeywords:"function constructor destructor procedure",end:/[:;]/,
keywords:"function constructor|10 destructor|10 procedure|10",
contains:[e.TITLE_MODE,{className:"params",begin:/\(/,end:/\)/,keywords:n,
contains:[a,r,t].concat(s)},t].concat(s)};return{name:"Delphi",
aliases:["dpr","dfm","pas","pascal"],case_insensitive:!0,keywords:n,
illegal:/"|\$[G-Zg-z]|\/\*|<\/|\|/,contains:[a,r,e.NUMBER_MODE,{
className:"number",relevance:0,variants:[{begin:"\\$[0-9A-Fa-f]+"},{
begin:"&[0-7]+"},{begin:"%[01]+"}]},i,o,t].concat(s)}},grmr_dockerfile:e=>({
name:"Dockerfile",aliases:["docker"],case_insensitive:!0,
keywords:["from","maintainer","expose","env","arg","user","onbuild","stopsignal"],
contains:[e.HASH_COMMENT_MODE,e.APOS_STRING_MODE,e.QUOTE_STRING_MODE,e.NUMBER_MODE,{
beginKeywords:"run cmd entrypoint volume add copy workdir label healthcheck shell",
starts:{end:/[^\\]$/,subLanguage:"bash"}}],illegal:"</"}),grmr_erlang:e=>{
const n="[a-z'][a-zA-Z0-9_']*",s="("+n+":"+n+"|"+n+")",t={
keyword:"after and andalso|10 band begin bnot bor bsl bzr bxor case catch cond div end fun if let not of orelse|10 query receive rem try when xor",
literal:"false true"},a=e.COMMENT("%","$"),r={className:"number",
begin:"\\b(\\d+(_\\d+)*#[a-fA-F0-9]+(_[a-fA-F0-9]+)*|\\d+(_\\d+)*(\\.\\d+(_\\d+)*)?([eE][-+]?\\d+)?)",
relevance:0},i={begin:"fun\\s+"+n+"/\\d+"},o={begin:s+"\\(",end:"\\)",
returnBegin:!0,relevance:0,contains:[{begin:s,relevance:0},{begin:"\\(",
end:"\\)",endsWithParent:!0,returnEnd:!0,relevance:0}]},c={begin:/\{/,end:/\}/,
relevance:0},l={begin:"\\b_([A-Z][A-Za-z0-9_]*)?",relevance:0},d={
begin:"[A-Z][a-zA-Z0-9_]*",relevance:0},p={begin:"#"+e.UNDERSCORE_IDENT_RE,
relevance:0,returnBegin:!0,contains:[{begin:"#"+e.UNDERSCORE_IDENT_RE,
relevance:0},{begin:/\{/,end:/\}/,relevance:0}]},m={
beginKeywords:"fun receive if try case",end:"end",keywords:t}
;m.contains=[a,i,e.inherit(e.APOS_STRING_MODE,{className:""
}),m,o,e.QUOTE_STRING_MODE,r,c,l,d,p]
;const u=[a,i,m,o,e.QUOTE_STRING_MODE,r,c,l,d,p]
;o.contains[1].contains=u,c.contains=u,p.contains[1].contains=u;const b={
className:"params",begin:"\\(",end:"\\)",contains:u};return{name:"Erlang",
aliases:["erl"],keywords:t,illegal:"(</|\\*=|\\+=|-=|/\\*|\\*/|\\(\\*|\\*\\))",
contains:[{className:"function",begin:"^"+n+"\\s*\\(",end:"->",returnBegin:!0,
illegal:"\\(|#|//|/\\*|\\\\|:|;",contains:[b,e.inherit(e.TITLE_MODE,{begin:n})],
starts:{end:";|\\.",keywords:t,contains:u}},a,{begin:"^-",end:"\\.",relevance:0,
excludeEnd:!0,returnBegin:!0,keywords:{$pattern:"-"+e.IDENT_RE,
keyword:["-module","-record","-undef","-export","-ifdef","-ifndef","-author","-copyright","-doc","-vsn","-import","-include","-include_lib","-compile","-define","-else","-endif","-file","-behaviour","-behavior","-spec"].map((e=>e+"|1.5")).join(" ")
},contains:[b]},r,e.QUOTE_STRING_MODE,p,l,d,c,{begin:/\.$/}]}},grmr_fsharp:e=>{
const n={scope:"keyword",match:/\b(yield|return|let|do|match|use)!/
},s=["bool","byte","sbyte","int8","int16","int32","uint8","uint16","uint32","int","uint","int64","uint64","nativeint","unativeint","decimal","float","double","float32","single","char","string","unit","bigint","option","voption","list","array","seq","byref","exn","inref","nativeptr","obj","outref","voidptr","Result"],t={
keyword:["abstract","and","as","assert","base","begin","class","default","delegate","do","done","downcast","downto","elif","else","end","exception","extern","finally","fixed","for","fun","function","global","if","in","inherit","inline","interface","internal","lazy","let","match","member","module","mutable","namespace","new","of","open","or","override","private","public","rec","return","static","struct","then","to","try","type","upcast","use","val","void","when","while","with","yield"],
literal:["true","false","null","Some","None","Ok","Error","infinity","infinityf","nan","nanf"],
built_in:["not","ref","raise","reraise","dict","readOnlyDict","set","get","enum","sizeof","typeof","typedefof","nameof","nullArg","invalidArg","invalidOp","id","fst","snd","ignore","lock","using","box","unbox","tryUnbox","printf","printfn","sprintf","eprintf","eprintfn","fprintf","fprintfn","failwith","failwithf"],
"variable.constant":["__LINE__","__SOURCE_DIRECTORY__","__SOURCE_FILE__"]},a={
variants:[e.COMMENT(/\(\*(?!\))/,/\*\)/,{contains:["self"]
}),e.C_LINE_COMMENT_MODE]},r={scope:"variable",begin:/``/,end:/``/
},i=/\B('|\^)/,o={scope:"symbol",variants:[{match:g(i,/``.*?``/)},{
match:g(i,e.UNDERSCORE_IDENT_RE)}],relevance:0},c=({includeEqual:e})=>{let n
;n=e?"!%&*+-/<=>@^|~?":"!%&*+-/<>@^|~?"
;const s=g("[",...Array.from(n).map(d),"]"),t=_(s,/\./),a=g(t,m(t)),r=_(g(a,t,"*"),g(s,"+"))
;return{scope:"operator",match:_(r,/:\?>/,/:\?/,/:>/,/:=/,/::?/,/\$/),
relevance:0}},l=c({includeEqual:!0}),p=c({includeEqual:!1}),u=(n,i)=>({
begin:g(n,m(g(/\s*/,_(/\w/,/'/,/\^/,/#/,/``/,/\(/,/{\|/)))),beginScope:i,
end:m(_(/\n/,/=/)),relevance:0,keywords:e.inherit(t,{type:s}),
contains:[a,o,e.inherit(r,{scope:null}),p]
}),b=u(/:/,"operator"),v=u(/\bof\b/,"keyword"),f={
begin:[/(^|\s+)/,/type/,/\s+/,/[a-zA-Z_](\w|')*/],beginScope:{2:"keyword",
4:"title.class"},end:m(/\(|=|$/),keywords:t,contains:[a,e.inherit(r,{scope:null
}),o,{scope:"operator",match:/<|>/},b]},h={scope:"computation-expression",
match:/\b[_a-z]\w*(?=\s*\{)/},E={
begin:[/^\s*/,g(/#/,_("if","else","endif","line","nowarn","light","r","i","I","load","time","help","quit")),/\b/],
beginScope:{2:"meta"},end:m(/\s|$/)},w={
variants:[e.BINARY_NUMBER_MODE,e.C_NUMBER_MODE]},y={scope:"string",begin:/"/,
end:/"/,contains:[e.BACKSLASH_ESCAPE]},N={scope:"string",begin:/@"/,end:/"/,
contains:[{match:/""/},e.BACKSLASH_ESCAPE]},x={scope:"string",begin:/"""/,
end:/"""/,relevance:2},k={scope:"subst",begin:/\{/,end:/\}/,keywords:t},O={
scope:"string",begin:/\$"/,end:/"/,contains:[{match:/\{\{/},{match:/\}\}/
},e.BACKSLASH_ESCAPE,k]},M={scope:"string",begin:/(\$@|@\$)"/,end:/"/,
contains:[{match:/\{\{/},{match:/\}\}/},{match:/""/},e.BACKSLASH_ESCAPE,k]},S={
scope:"string",begin:/\$"""/,end:/"""/,contains:[{match:/\{\{/},{match:/\}\}/
},k],relevance:2},C={scope:"string",
match:g(/'/,_(/[^\\']/,/\\(?:.|\d{3}|x[a-fA-F\d]{2}|u[a-fA-F\d]{4}|U[a-fA-F\d]{8})/),/'/)
};return k.contains=[M,O,N,y,C,n,a,r,b,h,E,w,o,l],{name:"F#",
aliases:["fs","f#"],keywords:t,illegal:/\/\*/,classNameAliases:{
"computation-expression":"keyword"},contains:[n,{variants:[S,M,O,x,N,y,C]
},a,r,f,{scope:"meta",begin:/\[</,end:/>\]/,relevance:2,contains:[r,x,N,y,C,w]
},v,b,h,E,w,o,l]}},grmr_haskell:e=>{const n={
variants:[e.COMMENT("--","$"),e.COMMENT(/\{-/,/-\}/,{contains:["self"]})]},s={
className:"meta",begin:/\{-#/,end:/#-\}/},t={className:"meta",begin:"^#",end:"$"
},a={className:"type",begin:"\\b[A-Z][\\w']*",relevance:0},r={begin:"\\(",
end:"\\)",illegal:'"',contains:[s,t,{className:"type",
begin:"\\b[A-Z][\\w]*(\\((\\.\\.|,|\\w+)\\))?"},e.inherit(e.TITLE_MODE,{
begin:"[_a-z][\\w']*"}),n]},i="([0-9a-fA-F]_*)+",o={className:"number",
relevance:0,variants:[{
match:"\\b(([0-9]_*)+)(\\.(([0-9]_*)+))?([eE][+-]?(([0-9]_*)+))?\\b"},{
match:`\\b0[xX]_*(${i})(\\.(${i}))?([pP][+-]?(([0-9]_*)+))?\\b`},{
match:"\\b0[oO](([0-7]_*)+)\\b"},{match:"\\b0[bB](([01]_*)+)\\b"}]};return{
name:"Haskell",aliases:["hs"],
keywords:"let in if then else case of where do module import hiding qualified type data newtype deriving class instance as default infix infixl infixr foreign export ccall stdcall cplusplus jvm dotnet safe unsafe family forall mdo proc rec",
contains:[{beginKeywords:"module",end:"where",keywords:"module where",
contains:[r,n],illegal:"\\W\\.|;"},{begin:"\\bimport\\b",end:"$",
keywords:"import qualified as hiding",contains:[r,n],illegal:"\\W\\.|;"},{
className:"class",begin:"^(\\s*)?(class|instance)\\b",end:"where",
keywords:"class family instance where",contains:[a,r,n]},{className:"class",
begin:"\\b(data|(new)?type)\\b",end:"$",
keywords:"data family type newtype deriving",contains:[s,a,r,{begin:/\{/,
end:/\}/,contains:r.contains},n]},{beginKeywords:"default",end:"$",
contains:[a,r,n]},{beginKeywords:"infix infixl infixr",end:"$",
contains:[e.C_NUMBER_MODE,n]},{begin:"\\bforeign\\b",end:"$",
keywords:"foreign import export ccall stdcall cplusplus jvm dotnet safe unsafe",
contains:[a,e.QUOTE_STRING_MODE,n]},{className:"meta",
begin:"#!\\/usr\\/bin\\/env runhaskell",end:"$"
},s,t,e.QUOTE_STRING_MODE,o,a,e.inherit(e.TITLE_MODE,{begin:"^[_a-z][\\w']*"
}),n,{begin:"->|<-"}]}},grmr_lisp:e=>{
var n="[a-zA-Z_\\-+\\*\\/<=>&#][a-zA-Z0-9_\\-+*\\/<=>&#!]*",s="\\|[^]*?\\|",t="(-|\\+)?\\d+(\\.\\d+|\\/\\d+)?((d|e|f|l|s|D|E|F|L|S)(\\+|-)?\\d+)?",a={
className:"literal",begin:"\\b(t{1}|nil)\\b"},r={className:"number",variants:[{
begin:t,relevance:0},{begin:"#(b|B)[0-1]+(/[0-1]+)?"},{
begin:"#(o|O)[0-7]+(/[0-7]+)?"},{begin:"#(x|X)[0-9a-fA-F]+(/[0-9a-fA-F]+)?"},{
begin:"#(c|C)\\("+t+" +"+t,end:"\\)"}]},i=e.inherit(e.QUOTE_STRING_MODE,{
illegal:null}),o=e.COMMENT(";","$",{relevance:0}),c={begin:"\\*",end:"\\*"},l={
className:"symbol",begin:"[:&]"+n},d={begin:n,relevance:0},p={begin:s},m={
contains:[r,i,c,l,{begin:"\\(",end:"\\)",contains:["self",a,i,r,d]},d],
variants:[{begin:"['`]\\(",end:"\\)"},{begin:"\\(quote ",end:"\\)",keywords:{
name:"quote"}},{begin:"'"+s}]},u={variants:[{begin:"'"+n},{
begin:"#'"+n+"(::"+n+")*"}]},b={begin:"\\(\\s*",end:"\\)"},g={endsWithParent:!0,
relevance:0};return b.contains=[{className:"name",variants:[{begin:n,relevance:0
},{begin:s}]},g],g.contains=[m,u,b,a,r,i,o,c,l,p,d],{name:"Lisp",illegal:/\S/,
contains:[r,e.SHEBANG(),a,i,o,m,u,b,d]}},grmr_powershell:e=>{const n={
$pattern:/-?[A-z\.\-]+\b/,
keyword:"if else foreach return do while until elseif begin for trap data dynamicparam end break throw param continue finally in switch exit filter try process catch hidden static parameter",
built_in:"ac asnp cat cd CFS chdir clc clear clhy cli clp cls clv cnsn compare copy cp cpi cpp curl cvpa dbp del diff dir dnsn ebp echo|0 epal epcsv epsn erase etsn exsn fc fhx fl ft fw gal gbp gc gcb gci gcm gcs gdr gerr ghy gi gin gjb gl gm gmo gp gps gpv group gsn gsnp gsv gtz gu gv gwmi h history icm iex ihy ii ipal ipcsv ipmo ipsn irm ise iwmi iwr kill lp ls man md measure mi mount move mp mv nal ndr ni nmo npssc nsn nv ogv oh popd ps pushd pwd r rbp rcjb rcsn rd rdr ren ri rjb rm rmdir rmo rni rnp rp rsn rsnp rujb rv rvpa rwmi sajb sal saps sasv sbp sc scb select set shcm si sl sleep sls sort sp spjb spps spsv start stz sujb sv swmi tee trcm type wget where wjb write"
},s={begin:"`[\\s\\S]",relevance:0},t={className:"variable",variants:[{
begin:/\$\B/},{className:"keyword",begin:/\$this/},{begin:/\$[\w\d][\w\d_:]*/}]
},a={className:"string",variants:[{begin:/"/,end:/"/},{begin:/@"/,end:/^"@/}],
contains:[s,t,{className:"variable",begin:/\$[A-z]/,end:/[^A-z]/}]},r={
className:"string",variants:[{begin:/'/,end:/'/},{begin:/@'/,end:/^'@/}]
},i=e.inherit(e.COMMENT(null,null),{variants:[{begin:/#/,end:/$/},{begin:/<#/,
end:/#>/}],contains:[{className:"doctag",variants:[{
begin:/\.(synopsis|description|example|inputs|outputs|notes|link|component|role|functionality)/
},{
begin:/\.(parameter|forwardhelptargetname|forwardhelpcategory|remotehelprunspace|externalhelp)\s+\S+/
}]}]}),o={className:"class",beginKeywords:"class enum",end:/\s*[{]/,
excludeEnd:!0,relevance:0,contains:[e.TITLE_MODE]},c={className:"function",
begin:/function\s+/,end:/\s*\{|$/,excludeEnd:!0,returnBegin:!0,relevance:0,
contains:[{begin:"function",relevance:0,className:"keyword"},{className:"title",
begin:/\w[\w\d]*((-)[\w\d]+)*/,relevance:0},{begin:/\(/,end:/\)/,
className:"params",relevance:0,contains:[t]}]},l={begin:/using\s/,end:/$/,
returnBegin:!0,contains:[a,r,{className:"keyword",
begin:/(using|assembly|command|module|namespace|type)/}]},d={
className:"function",begin:/\[.*\]\s*[\w]+[ ]??\(/,end:/$/,returnBegin:!0,
relevance:0,contains:[{className:"keyword",
begin:"(".concat(n.keyword.toString().replace(/\s/g,"|"),")\\b"),endsParent:!0,
relevance:0},e.inherit(e.TITLE_MODE,{endsParent:!0})]
},p=[d,i,s,e.NUMBER_MODE,a,r,{className:"built_in",variants:[{
begin:"(Add|Clear|Close|Copy|Enter|Exit|Find|Format|Get|Hide|Join|Lock|Move|New|Open|Optimize|Pop|Push|Redo|Remove|Rename|Reset|Resize|Search|Select|Set|Show|Skip|Split|Step|Switch|Undo|Unlock|Watch|Backup|Checkpoint|Compare|Compress|Convert|ConvertFrom|ConvertTo|Dismount|Edit|Expand|Export|Group|Import|Initialize|Limit|Merge|Mount|Out|Publish|Restore|Save|Sync|Unpublish|Update|Approve|Assert|Build|Complete|Confirm|Deny|Deploy|Disable|Enable|Install|Invoke|Register|Request|Restart|Resume|Start|Stop|Submit|Suspend|Uninstall|Unregister|Wait|Debug|Measure|Ping|Repair|Resolve|Test|Trace|Connect|Disconnect|Read|Receive|Send|Write|Block|Grant|Protect|Revoke|Unblock|Unprotect|Use|ForEach|Sort|Tee|Where)+(-)[\\w\\d]+"
}]},t,{className:"literal",begin:/\$(null|true|false)\b/},{
className:"selector-tag",begin:/@\B/,relevance:0}],m={begin:/\[/,end:/\]/,
excludeBegin:!0,excludeEnd:!0,relevance:0,contains:[].concat("self",p,{
begin:"(string|char|byte|int|long|bool|decimal|single|double|DateTime|xml|array|hashtable|void)",
className:"built_in",relevance:0},{className:"type",begin:/[\.\w\d]+/,
relevance:0})};return d.contains.unshift(m),{name:"PowerShell",
aliases:["pwsh","ps","ps1"],case_insensitive:!0,keywords:n,
contains:p.concat(o,c,l,{variants:[{className:"operator",
begin:"(-and|-as|-band|-bnot|-bor|-bxor|-casesensitive|-ccontains|-ceq|-cge|-cgt|-cle|-clike|-clt|-cmatch|-cne|-cnotcontains|-cnotlike|-cnotmatch|-contains|-creplace|-csplit|-eq|-exact|-f|-file|-ge|-gt|-icontains|-ieq|-ige|-igt|-ile|-ilike|-ilt|-imatch|-in|-ine|-inotcontains|-inotlike|-inotmatch|-ireplace|-is|-isnot|-isplit|-join|-le|-like|-lt|-match|-ne|-not|-notcontains|-notin|-notlike|-notmatch|-or|-regex|-replace|-shl|-shr|-split|-wildcard|-xor)\\b"
},{className:"literal",begin:/(-){1,2}[\w\d-]+/,relevance:0}]},m)}},
grmr_scala:e=>{const n=e.regex,s={className:"subst",variants:[{
begin:"\\$[A-Za-z0-9_]+"},{begin:/\$\{/,end:/\}/}]},t={className:"string",
variants:[{begin:'"""',end:'"""'},{begin:'"',end:'"',illegal:"\\n",
contains:[e.BACKSLASH_ESCAPE]},{begin:'[a-z]+"',end:'"',illegal:"\\n",
contains:[e.BACKSLASH_ESCAPE,s]},{className:"string",begin:'[a-z]+"""',
end:'"""',contains:[s],relevance:10}]},a={className:"type",
begin:"\\b[A-Z][A-Za-z0-9_]*",relevance:0},r={className:"title",
begin:/[^0-9\n\t "'(),.`{}\[\]:;][^\n\t "'(),.`{}\[\]:;]+|[^0-9\n\t "'(),.`{}\[\]:;=]/,
relevance:0},i={className:"class",beginKeywords:"class object trait type",
end:/[:={\[\n;]/,excludeEnd:!0,
contains:[e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE,{
beginKeywords:"extends with",relevance:10},{begin:/\[/,end:/\]/,excludeBegin:!0,
excludeEnd:!0,relevance:0,contains:[a]},{className:"params",begin:/\(/,end:/\)/,
excludeBegin:!0,excludeEnd:!0,relevance:0,contains:[a]},r]},o={
className:"function",beginKeywords:"def",end:n.lookahead(/[:={\[(\n;]/),
contains:[r]};return{name:"Scala",keywords:{literal:"true false null",
keyword:"type yield lazy override def with val var sealed abstract private trait object if then forSome for while do throw finally protected extends import final return else break new catch super class case package default try this match continue throws implicit export enum given"
},
contains:[e.C_LINE_COMMENT_MODE,e.C_BLOCK_COMMENT_MODE,t,a,o,i,e.C_NUMBER_MODE,{
begin:[/^\s*/,"extension",/\s+(?=[[(])/],beginScope:{2:"keyword"}},[{
begin:[/^\s*/,/end/,/\s+/,/(extension\b)?/],beginScope:{2:"keyword",4:"keyword"}
}],{match:/\.inline\b/},{begin:/\binline(?=\s)/,keywords:"inline"},{
begin:[/\(\s*/,/using/,/\s+(?!\))/],beginScope:{2:"keyword"}},{className:"meta",
begin:"@[A-Za-z]+"}]}},grmr_smalltalk:e=>{const n="[a-z][a-zA-Z0-9_]*",s={
className:"string",begin:"\\$.{1}"},t={className:"symbol",
begin:"#"+e.UNDERSCORE_IDENT_RE};return{name:"Smalltalk",aliases:["st"],
keywords:["self","super","nil","true","false","thisContext"],
contains:[e.COMMENT('"','"'),e.APOS_STRING_MODE,{className:"type",
begin:"\\b[A-Z][A-Za-z0-9_]*",relevance:0},{begin:n+":",relevance:0
},e.C_NUMBER_MODE,t,s,{begin:"\\|[ ]*"+n+"([ ]+"+n+")*[ ]*\\|",returnBegin:!0,
end:/\|/,illegal:/\S/,contains:[{begin:"(\\|[ ]*)?"+n}]},{begin:"#\\(",
end:"\\)",contains:[e.APOS_STRING_MODE,s,e.C_NUMBER_MODE,t]}]}},grmr_vhdl:e=>({
name:"VHDL",case_insensitive:!0,keywords:{
keyword:["abs","access","after","alias","all","and","architecture","array","assert","assume","assume_guarantee","attribute","begin","block","body","buffer","bus","case","component","configuration","constant","context","cover","disconnect","downto","default","else","elsif","end","entity","exit","fairness","file","for","force","function","generate","generic","group","guarded","if","impure","in","inertial","inout","is","label","library","linkage","literal","loop","map","mod","nand","new","next","nor","not","null","of","on","open","or","others","out","package","parameter","port","postponed","procedure","process","property","protected","pure","range","record","register","reject","release","rem","report","restrict","restrict_guarantee","return","rol","ror","select","sequence","severity","shared","signal","sla","sll","sra","srl","strong","subtype","then","to","transport","type","unaffected","units","until","use","variable","view","vmode","vprop","vunit","wait","when","while","with","xnor","xor"],
built_in:["boolean","bit","character","integer","time","delay_length","natural","positive","string","bit_vector","file_open_kind","file_open_status","std_logic","std_logic_vector","unsigned","signed","boolean_vector","integer_vector","std_ulogic","std_ulogic_vector","unresolved_unsigned","u_unsigned","unresolved_signed","u_signed","real_vector","time_vector"],
literal:["false","true","note","warning","error","failure","line","text","side","width"]
},illegal:/\{/,
contains:[e.C_BLOCK_COMMENT_MODE,e.COMMENT("--","$"),e.QUOTE_STRING_MODE,{
className:"number",
begin:"\\b(\\d(_|\\d)*#\\w+(\\.\\w+)?#([eE][-+]?\\d(_|\\d)*)?|\\d(_|\\d)*(\\.\\d(_|\\d)*)?([eE][-+]?\\d(_|\\d)*)?)",
relevance:0},{className:"string",begin:"'(U|X|0|1|Z|W|L|H|-)'",
contains:[e.BACKSLASH_ESCAPE]},{className:"symbol",
begin:"'[A-Za-z](_?[A-Za-z0-9])*",contains:[e.BACKSLASH_ESCAPE]}]}),
grmr_verilog:e=>{
const n=e.regex,s=["begin_keywords","celldefine","default_nettype","default_decay_time","default_trireg_strength","define","delay_mode_distributed","delay_mode_path","delay_mode_unit","delay_mode_zero","else","elsif","end_keywords","endcelldefine","endif","ifdef","ifndef","include","line","nounconnected_drive","pragma","resetall","timescale","unconnected_drive","undef","undefineall"]
;return{name:"Verilog",aliases:["v","sv","svh"],case_insensitive:!1,keywords:{
$pattern:/\$?[\w]+(\$[\w]+)*/,
keyword:["accept_on","alias","always","always_comb","always_ff","always_latch","and","assert","assign","assume","automatic","before","begin","bind","bins","binsof","bit","break","buf|0","bufif0","bufif1","byte","case","casex","casez","cell","chandle","checker","class","clocking","cmos","config","const","constraint","context","continue","cover","covergroup","coverpoint","cross","deassign","default","defparam","design","disable","dist","do","edge","else","end","endcase","endchecker","endclass","endclocking","endconfig","endfunction","endgenerate","endgroup","endinterface","endmodule","endpackage","endprimitive","endprogram","endproperty","endspecify","endsequence","endtable","endtask","enum","event","eventually","expect","export","extends","extern","final","first_match","for","force","foreach","forever","fork","forkjoin","function","generate|5","genvar","global","highz0","highz1","if","iff","ifnone","ignore_bins","illegal_bins","implements","implies","import","incdir","include","initial","inout","input","inside","instance","int","integer","interconnect","interface","intersect","join","join_any","join_none","large","let","liblist","library","local","localparam","logic","longint","macromodule","matches","medium","modport","module","nand","negedge","nettype","new","nexttime","nmos","nor","noshowcancelled","not","notif0","notif1","or","output","package","packed","parameter","pmos","posedge","primitive","priority","program","property","protected","pull0","pull1","pulldown","pullup","pulsestyle_ondetect","pulsestyle_onevent","pure","rand","randc","randcase","randsequence","rcmos","real","realtime","ref","reg","reject_on","release","repeat","restrict","return","rnmos","rpmos","rtran","rtranif0","rtranif1","s_always","s_eventually","s_nexttime","s_until","s_until_with","scalared","sequence","shortint","shortreal","showcancelled","signed","small","soft","solve","specify","specparam","static","string","strong","strong0","strong1","struct","super","supply0","supply1","sync_accept_on","sync_reject_on","table","tagged","task","this","throughout","time","timeprecision","timeunit","tran","tranif0","tranif1","tri","tri0","tri1","triand","trior","trireg","type","typedef","union","unique","unique0","unsigned","until","until_with","untyped","use","uwire","var","vectored","virtual","void","wait","wait_order","wand","weak","weak0","weak1","while","wildcard","wire","with","within","wor","xnor","xor"],
literal:["null"],
built_in:["$finish","$stop","$exit","$fatal","$error","$warning","$info","$realtime","$time","$printtimescale","$bitstoreal","$bitstoshortreal","$itor","$signed","$cast","$bits","$stime","$timeformat","$realtobits","$shortrealtobits","$rtoi","$unsigned","$asserton","$assertkill","$assertpasson","$assertfailon","$assertnonvacuouson","$assertoff","$assertcontrol","$assertpassoff","$assertfailoff","$assertvacuousoff","$isunbounded","$sampled","$fell","$changed","$past_gclk","$fell_gclk","$changed_gclk","$rising_gclk","$steady_gclk","$coverage_control","$coverage_get","$coverage_save","$set_coverage_db_name","$rose","$stable","$past","$rose_gclk","$stable_gclk","$future_gclk","$falling_gclk","$changing_gclk","$display","$coverage_get_max","$coverage_merge","$get_coverage","$load_coverage_db","$typename","$unpacked_dimensions","$left","$low","$increment","$clog2","$ln","$log10","$exp","$sqrt","$pow","$floor","$ceil","$sin","$cos","$tan","$countbits","$onehot","$isunknown","$fatal","$warning","$dimensions","$right","$high","$size","$asin","$acos","$atan","$atan2","$hypot","$sinh","$cosh","$tanh","$asinh","$acosh","$atanh","$countones","$onehot0","$error","$info","$random","$dist_chi_square","$dist_erlang","$dist_exponential","$dist_normal","$dist_poisson","$dist_t","$dist_uniform","$q_initialize","$q_remove","$q_exam","$async$and$array","$async$nand$array","$async$or$array","$async$nor$array","$sync$and$array","$sync$nand$array","$sync$or$array","$sync$nor$array","$q_add","$q_full","$psprintf","$async$and$plane","$async$nand$plane","$async$or$plane","$async$nor$plane","$sync$and$plane","$sync$nand$plane","$sync$or$plane","$sync$nor$plane","$system","$display","$displayb","$displayh","$displayo","$strobe","$strobeb","$strobeh","$strobeo","$write","$readmemb","$readmemh","$writememh","$value$plusargs","$dumpvars","$dumpon","$dumplimit","$dumpports","$dumpportson","$dumpportslimit","$writeb","$writeh","$writeo","$monitor","$monitorb","$monitorh","$monitoro","$writememb","$dumpfile","$dumpoff","$dumpall","$dumpflush","$dumpportsoff","$dumpportsall","$dumpportsflush","$fclose","$fdisplay","$fdisplayb","$fdisplayh","$fdisplayo","$fstrobe","$fstrobeb","$fstrobeh","$fstrobeo","$swrite","$swriteb","$swriteh","$swriteo","$fscanf","$fread","$fseek","$fflush","$feof","$fopen","$fwrite","$fwriteb","$fwriteh","$fwriteo","$fmonitor","$fmonitorb","$fmonitorh","$fmonitoro","$sformat","$sformatf","$fgetc","$ungetc","$fgets","$sscanf","$rewind","$ftell","$ferror"]
},contains:[e.C_BLOCK_COMMENT_MODE,e.C_LINE_COMMENT_MODE,e.QUOTE_STRING_MODE,{
scope:"number",contains:[e.BACKSLASH_ESCAPE],variants:[{
begin:/\b((\d+'([bhodBHOD]))[0-9xzXZa-fA-F_]+)/},{
begin:/\B(('([bhodBHOD]))[0-9xzXZa-fA-F_]+)/},{begin:/\b[0-9][0-9_]*/,
relevance:0}]},{scope:"variable",variants:[{begin:"#\\((?!parameter).+\\)"},{
begin:"\\.\\w+",relevance:0}]},{scope:"variable.constant",
match:n.concat(/`/,n.either("__FILE__","__LINE__"))},{scope:"meta",
begin:n.concat(/`/,n.either(...s)),end:/$|\/\/|\/\*/,returnEnd:!0,keywords:s}]}
},grmr_matlab:e=>{var n={relevance:0,contains:[{begin:"('|\\.')+"}]};return{
name:"Matlab",keywords:{
keyword:"arguments break case catch classdef continue else elseif end enumeration events for function global if methods otherwise parfor persistent properties return spmd switch try while",
built_in:"sin sind sinh asin asind asinh cos cosd cosh acos acosd acosh tan tand tanh atan atand atan2 atanh sec secd sech asec asecd asech csc cscd csch acsc acscd acsch cot cotd coth acot acotd acoth hypot exp expm1 log log1p log10 log2 pow2 realpow reallog realsqrt sqrt nthroot nextpow2 abs angle complex conj imag real unwrap isreal cplxpair fix floor ceil round mod rem sign airy besselj bessely besselh besseli besselk beta betainc betaln ellipj ellipke erf erfc erfcx erfinv expint gamma gammainc gammaln psi legendre cross dot factor isprime primes gcd lcm rat rats perms nchoosek factorial cart2sph cart2pol pol2cart sph2cart hsv2rgb rgb2hsv zeros ones eye repmat rand randn linspace logspace freqspace meshgrid accumarray size length ndims numel disp isempty isequal isequalwithequalnans cat reshape diag blkdiag tril triu fliplr flipud flipdim rot90 find sub2ind ind2sub bsxfun ndgrid permute ipermute shiftdim circshift squeeze isscalar isvector ans eps realmax realmin pi i|0 inf nan isnan isinf isfinite j|0 why compan gallery hadamard hankel hilb invhilb magic pascal rosser toeplitz vander wilkinson max min nanmax nanmin mean nanmean type table readtable writetable sortrows sort figure plot plot3 scatter scatter3 cellfun legend intersect ismember procrustes hold num2cell "
},illegal:'(//|"|#|/\\*|\\s+/\\w+)',contains:[{className:"function",
beginKeywords:"function",end:"$",contains:[e.UNDERSCORE_TITLE_MODE,{
className:"params",variants:[{begin:"\\(",end:"\\)"},{begin:"\\[",end:"\\]"}]}]
},{className:"built_in",begin:/true|false/,relevance:0,starts:n},{
begin:"[a-zA-Z][a-zA-Z_0-9]*('|\\.')+",relevance:0},{className:"number",
begin:e.C_NUMBER_RE,relevance:0,starts:n},{className:"string",begin:"'",end:"'",
contains:[{begin:"''"}]},{begin:/\]|\}|\)/,relevance:0,starts:n},{
className:"string",begin:'"',end:'"',contains:[{begin:'""'}],starts:n
},e.COMMENT("^\\s*%\\{\\s*$","^\\s*%\\}\\s*$"),e.COMMENT("%","$")]}}})
;const Pe=se;for(const e of Object.keys(Fe)){
const n=e.replace("grmr_","").replace("_","-");Pe.registerLanguage(n,Fe[e])}
return Pe}()
;"object"==typeof exports&&"undefined"!=typeof module&&(module.exports=hljs);